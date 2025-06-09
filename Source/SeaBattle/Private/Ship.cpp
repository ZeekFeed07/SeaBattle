// Copyright (c) 2025 Azizkhon Ishanov. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#include "Ship.h"


AShip::AShip()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AShip::BeginPlay()
{
	Super::BeginPlay();
	SetShipLength(GetShipLength());
}

void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

EShipLength AShip::GetShipLength() const
{
	return _Length;
}

EShipDirection AShip::GetShipDirection() const
{
	return _Direction;
}

int32 AShip::GetNumOfDestroyedParts() const
{
	return _DestroyedParts;
}

bool AShip::IsPlaced() const
{
	return _bPlaced;
}

void AShip::SetShipLength(EShipLength NewLength)
{
	_Length = NewLength;
	OnLengthChanged();
}

void AShip::SetShipDirection(EShipDirection NewDirection)
{
	_Direction = NewDirection;
	OnDirectionChanged();
}

void AShip::SetPlacedShip()
{
	_bPlaced = true;
}

void AShip::SetUnplacedShip()
{
	_bPlaced = false;
}

bool AShip::DestroyPart()
{
	if (_DestroyedParts <= 0)
	{
		return false;
	}
	else if (_DestroyedParts == 1)
	{
		OnShipDestroyed();
	}

	--_DestroyedParts;
	return true;
}