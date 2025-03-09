// Copyright (c) 2024 Azizkhon Ishanov. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#include "Ship.h"

AShip::AShip()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AShip::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 AShip::GetShipSize() const
{
	return _Size;
}

void AShip::SetShipSize(int32 NewSize)
{
	_Size = NewSize;
}

EShipDirection AShip::GetDirection() const
{
	return _Direction;
}

void AShip::SetDirection(EShipDirection NewDirection)
{
	_Direction = NewDirection;
}