// Copyright (c) 2024 Azizkhon Ishanov. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#include "SeaFieldCell.h"

ASeaFieldCell::ASeaFieldCell()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASeaFieldCell::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASeaFieldCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASeaFieldCell::SetCoord(FIntPoint NewCoord)
{
	_Coord = NewCoord;
}

FIntPoint ASeaFieldCell::GetCoord() const
{
	return _Coord;
}

FVector ASeaFieldCell::GetSize() const
{
	return _Size;
}