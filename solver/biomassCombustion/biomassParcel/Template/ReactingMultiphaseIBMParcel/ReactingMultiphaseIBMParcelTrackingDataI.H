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

template<class ParcelType>
template<class TrackCloudType>
inline Foam::ReactingMultiphaseIBMParcel<ParcelType>::trackingData::trackingData
(
    const TrackCloudType& cloud,
    trackPart part
)
:
    ParcelType::trackingData(cloud, part),
    rhoavgInterp_
    (
        interpolation<scalar>::New
        (
            cloud.solution().interpolationSchemes(),
            cloud.rhoavg()
        )
    ),
    UavgInterp_
    (
        interpolation<vector>::New
        (
            cloud.solution().interpolationSchemes(),
            cloud.Uavg()
        )
    ),
    muavgInterp_
    (
        interpolation<scalar>::New
        (
            cloud.solution().interpolationSchemes(),
            cloud.muavg()
        )
    ),
    alphaavgInterp_
    (
        interpolation<scalar>::New
        (
            cloud.solution().interpolationSchemes(),
            cloud.alphaavg()
        )
    ),
    TavgInterp_
    (
        interpolation<scalar>::New
        (
            cloud.solution().interpolationSchemes(),
            cloud.Tavg()
        )
    ),
    CpavgInterp_
    (
        interpolation<scalar>::New
        (
            cloud.solution().interpolationSchemes(),
            cloud.cpavg()
        )
    ),
    kappaavgInterp_
    (
        interpolation<scalar>::New
        (
            cloud.solution().interpolationSchemes(),
            cloud.kappaavg()
        )
    ),
    alphac_(Zero),
    kappac_(Zero)
{}


template<class ParcelType>
inline const Foam::interpolation<Foam::scalar>&
Foam::ReactingMultiphaseIBMParcel<ParcelType>::trackingData::rhoavgInterp() const
{
    return rhoavgInterp_();
}


template<class ParcelType>
inline const Foam::interpolation<Foam::vector>&
Foam::ReactingMultiphaseIBMParcel<ParcelType>::trackingData::UavgInterp() const
{
    return UavgInterp_();
}


template<class ParcelType>
inline const Foam::interpolation<Foam::scalar>&
Foam::ReactingMultiphaseIBMParcel<ParcelType>::trackingData::muavgInterp() const
{
    return muavgInterp_();
}


template<class ParcelType>
inline const Foam::interpolation<Foam::scalar>&
Foam::ReactingMultiphaseIBMParcel<ParcelType>::trackingData::alphaavgInterp() const
{
    return alphaavgInterp_();
}


template<class ParcelType>
inline const Foam::interpolation<Foam::scalar>&
Foam::ReactingMultiphaseIBMParcel<ParcelType>::trackingData::TavgInterp() const
{
    return TavgInterp_();
}


template<class ParcelType>
inline const Foam::interpolation<Foam::scalar>&
Foam::ReactingMultiphaseIBMParcel<ParcelType>::trackingData::CpavgInterp() const
{
    return CpavgInterp_();
}


template<class ParcelType>
inline const Foam::interpolation<Foam::scalar>&
Foam::ReactingMultiphaseIBMParcel<ParcelType>::trackingData::kappaavgInterp() const
{
    return kappaavgInterp_();
}


template<class ParcelType>
inline Foam::scalar Foam::ReactingMultiphaseIBMParcel<ParcelType>::trackingData::alphac() const
{
    return alphac_;
}


template<class ParcelType>
inline Foam::scalar& Foam::ReactingMultiphaseIBMParcel<ParcelType>::trackingData::alphac()
{
    return alphac_;
}


template<class ParcelType>
inline Foam::scalar Foam::ReactingMultiphaseIBMParcel<ParcelType>::trackingData::kappac() const
{
    return kappac_;
}


template<class ParcelType>
inline Foam::scalar& Foam::ReactingMultiphaseIBMParcel<ParcelType>::trackingData::kappac()
{
    return kappac_;
}

// ************************************************************************* //
