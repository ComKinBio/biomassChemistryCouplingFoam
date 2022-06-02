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

\*---------------------------------------------------------------------------*/

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
inline const Foam::ReactingMultiphaseIBMCloud<CloudType>&
Foam::ReactingMultiphaseIBMCloud<CloudType>::cloudCopy() const
{
    return cloudCopyPtr_();
}


template<class CloudType>
inline const typename CloudType::particleType::constantProperties&
Foam::ReactingMultiphaseIBMCloud<CloudType>::constProps() const
{
    return constProps_;
}


template<class CloudType>
inline typename CloudType::particleType::constantProperties&
Foam::ReactingMultiphaseIBMCloud<CloudType>::constProps()
{
    return constProps_;
}


template<class CloudType>
inline const Foam::volVectorField& Foam::ReactingMultiphaseIBMCloud<CloudType>::Uavg() const
{
    return Uavg_;
}


template<class CloudType>
inline const Foam::volScalarField& Foam::ReactingMultiphaseIBMCloud<CloudType>::rhoavg() const
{
    return rhoavg_;
}


template<class CloudType>
inline const Foam::volScalarField& Foam::ReactingMultiphaseIBMCloud<CloudType>::muavg() const
{
    return muavg_;
}


template<class CloudType>
inline const Foam::volScalarField& Foam::ReactingMultiphaseIBMCloud<CloudType>::alphaavg() const
{
    return alphaavg_;
}


template<class CloudType>
inline const Foam::volScalarField& Foam::ReactingMultiphaseIBMCloud<CloudType>::Tavg() const
{
    return Tavg_;
}


template<class CloudType>
inline const Foam::volScalarField& Foam::ReactingMultiphaseIBMCloud<CloudType>::kappaavg() const
{
    return kappaavg_;
}


template<class CloudType>
inline const Foam::volScalarField& Foam::ReactingMultiphaseIBMCloud<CloudType>::cpavg() const
{
    return cpavg_;
}


template<class CloudType>
inline const Foam::PyrolysisModel
<
    Foam::ReactingMultiphaseIBMCloud<CloudType>
>&
Foam::ReactingMultiphaseIBMCloud<CloudType>::pyrolysis() const
{
    return pyrolysisModel_;
}


template<class CloudType>
inline Foam::PyrolysisModel
<
    Foam::ReactingMultiphaseIBMCloud<CloudType>
>&
Foam::ReactingMultiphaseIBMCloud<CloudType>::pyrolysis()
{
    return pyrolysisModel_();
}


template<class CloudType>
inline const Foam::CharOxidizationModel
<
    Foam::ReactingMultiphaseIBMCloud<CloudType>
>&
Foam::ReactingMultiphaseIBMCloud<CloudType>::charOxidization() const
{
    return charOxidizationModel_;
}


template<class CloudType>
inline Foam::CharOxidizationModel
<
    Foam::ReactingMultiphaseIBMCloud<CloudType>
>&
Foam::ReactingMultiphaseIBMCloud<CloudType>::charOxidization()
{
    return charOxidizationModel_();
}


template<class CloudType>
inline const Foam::tmp<Foam::volScalarField>
Foam::ReactingMultiphaseIBMCloud<CloudType>::np() const
{
    tmp<volScalarField> tnp
    (
        volScalarField::New
        (
            this->name() + ":np",
            this->mesh_,
            dimensionedScalar(dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );

    volScalarField& np = tnp.ref();
    forAllConstIter(typename ReactingMultiphaseIBMCloud<CloudType>, *this, iter)
    {
        const parcelType& p = iter();
        const label celli = p.cell();

        np[celli] += p.nParticle();
    }

    return tnp;
}


template<class CloudType>
inline const Foam::tmp<Foam::volScalarField>
Foam::ReactingMultiphaseIBMCloud<CloudType>::parcelVolumeField() const
{
    tmp<volScalarField> parcelVolume
    (
        volScalarField::New
        (
            this->name() + ":parcelVolumeField",
            this->mesh_,
            dimensionedScalar(dimVolume, 0)
        )
    );

    volScalarField& pV = parcelVolume.ref();
    forAllConstIter(typename ReactingMultiphaseIBMCloud<CloudType>, *this, iter)
    {
        const parcelType& p = iter();
        const label celli = p.cell();

        pV[celli] += p.nParticle()*p.volume();
    }
    
    pV.correctBoundaryConditions();

    return parcelVolume;
}


template<class CloudType>
inline const Foam::tmp<Foam::volScalarField>
Foam::ReactingMultiphaseIBMCloud<CloudType>::alpha() const
{
    tmp<volScalarField> talpha
    (
        volScalarField::New
        (
            this->name() + ":alpha",
            this->mesh_,
            dimensionedScalar(dimless, 0)
        )
    );

    scalarField& alpha = talpha.ref().primitiveFieldRef();
    forAllConstIter(typename ReactingMultiphaseIBMCloud<CloudType>, *this, iter)
    {
        const parcelType& p = iter();
        const label celli = p.cell();

        alpha[celli] += p.nParticle()*p.mass();
    }

    alpha /= (this->mesh_.V()*this->rho_);

    return talpha;
}


// ************************************************************************* //
