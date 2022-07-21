/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    coalChemistryFoam

Description
    Transient solver for compressible, turbulent flow, with coal and limestone
    particle clouds, an energy source, and combustion.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "turbulentFluidThermoModel.H"
#include "coalChemistryTurbulenceModel.H"
#include "biomassCloud.H"
#include "psiReactionThermo.H"
#include "CombustionModel.H"
#include "fvOptions.H"
#include "radiationModel.H"
#include "SLGThermo.H"
#include "pimpleControl.H"
// #include "simpleControl.H" //added for DBM
#include "pressureControl.H"
#include "localEulerDdtScheme.H"
#include "fvcSmooth.H"
#include "coarserGrid.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    #include "postProcess.H"

    #include "setRootCaseLists.H"
    #include "createTime.H"
    #include "createMesh.H"
    pimpleControl pimple(mesh);
    #include "createTimeControls.H"
    #include "createFields.H"
    #include "createFieldRefs.H"
    #include "initContinuityErrs.H"

    turbulence->validate();

    if (!LTS)
    {
        #include "compressibleCourantNo.H"
        #include "setInitialDeltaT.H"
    }

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< "\nStarting time loop\n" << endl;

    while (runTime.run())
    {
        #include "readTimeControls.H"

        if (LTS)
        {
            #include "setRDeltaT.H"
        }
        else
        {
            #include "compressibleCourantNo.H"
            #include "setDeltaT.H"
        }

        runTime++;

        Info<< "Time = " << runTime.timeName() << nl << endl;
        
        pDyn = 0.5*rhoc*magSqr(Uc);
        
        // Update continuous phase volume fraction field
        alphac = max(1.0 - bioCloud.theta(), alphacMin);
        alphac.correctBoundaryConditions();
      
        if (useTFMGas)
        {
            parcelVolumeField = bioCloud.parcelVolumeField();
            alphacavg = TFM.averagedAlphaField(parcelVolumeField);       
            Ucavg = TFM.averagedField(Uc, alphacavg);
            rhoavg = TFM.averagedField(rhoc, alphacavg);
            Tavg = TFM.averagedField(T, alphacavg);
            muavg = TFM.averagedField(thermo.mu(), alphacavg);
            kappaavg = TFM.averagedField(thermo.kappa(), alphacavg);
            Cpavg = TFM.averagedField(thermo.Cp(), alphacavg);
        }

        bioCloud.evolve();

        alphacavg.correctBoundaryConditions();
        alphacf = fvc::interpolate(alphacavg);
        alphaRhoPhic = alphacf*rhocPhic;


        volScalarField::Internal averagedSrho = bioCloud.Srho();
        fvScalarMatrix averagedSrhoRho = bioCloud.Srho(rhoc);
        fvVectorMatrix averagedSU = bioCloud.SU(Uc);
        volScalarField& hee = thermo.he();
        fvScalarMatrix averagedSh = bioCloud.Sh(hee);
                
        if (useTFMSource)
        {
            
            scalarField& averagedSrhoIninterFeildRef = averagedSrho;
            averagedSrhoIninterFeildRef = TFM.averagedSource(averagedSrhoIninterFeildRef);
            
            scalarField& averagedSrhoRhoIninterFeildRef = averagedSrhoRho.source();
            averagedSrhoRhoIninterFeildRef= TFM.averagedSource(averagedSrhoRhoIninterFeildRef);
            
            vectorField& averagedSUIninterFeildRef = averagedSU.source();
            averagedSUIninterFeildRef= TFM.averagedSource(averagedSUIninterFeildRef); 
            
            scalarField& averagedShIninterFeildRef = averagedSh.source();
            averagedShIninterFeildRef = TFM.averagedSource(averagedShIninterFeildRef);
        }
        
//         alphacavg = alphac;

        #include "rhocEqn.H"
        // --- Pressure-velocity PIMPLE corrector loop
        while (pimple.loop())
        {
            #include "UcEqn.H"
            #include "YEqn.H"
            #include "EEqn.H"
// Info<<"Uc: "<<Uc <<endl;
// Info<<"p: "<<p <<endl;
            // --- Pressure corrector loop
            while (pimple.correct())
            {
                #include "pEqn.H"  
            }

            if (pimple.turbCorr())
            {
                turbulence->correct();
            }
        }

        rhoc = thermo.rho();

        runTime.write();

        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
