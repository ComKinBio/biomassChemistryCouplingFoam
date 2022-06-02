tmp<fv::convectionScheme<scalar>> mvConvection
(
    fv::convectionScheme<scalar>::New
    (
        mesh,
        fields,
        alphaRhoPhic,
        mesh.divScheme("div(alphaRhoPhi,Yi_h)")
    )
);



{
    combustion->correct();
    Qdot = combustion->Qdot();
    volScalarField Yt(0.0*Y[0]);
    
    const volScalarField muEff(turbulence->muEff());

    forAll(Y, i)
    {
        if (i != inertIndex && composition.active(i))
        {
            volScalarField& Yi = Y[i];

            fvScalarMatrix averagedSYi = bioCloud.SYi(i, Yi);
            
            if (i == O2Id || i == H2OId || i == CO2Id || i == H2Id || i == COId || i == CH4OId || i == tarId)
            {
                if (useTFMSource)
                {
                    scalarField& averagedSYiIninterFeildRef = averagedSYi.source();
                    averagedSYiIninterFeildRef = TFM.averagedSource(averagedSYiIninterFeildRef);
                    
                }
            }
            
            fvScalarMatrix YiEqn
            (
                fvm::ddt(alphac, rhoc, Yi)
              + mvConvection->fvmDiv(alphaRhoPhic, Yi)
              - fvm::laplacian
                (
                    fvc::interpolate(alphac)
                    *fvc::interpolate(muEff),
                    Yi
                )
              ==
//                 bioCloud.SYi(i, Yi)
                averagedSYi
              + combustion->R(Yi)
              + fvOptions(rhoc, Yi)
            );

            YiEqn.relax();

            fvOptions.constrain(YiEqn);

//             YiEqn.solve(mesh.solver("Yi"));
            YiEqn.solve();

            fvOptions.correct(Yi);

            Yi.max(0.0);
            Yt += Yi;
        }
    }

    Y[inertIndex] = scalar(1) - Yt;
    Y[inertIndex].max(0.0);
}
