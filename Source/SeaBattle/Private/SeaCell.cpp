// Copyright (c) 2025 Azizkhon Ishanov. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#include "SeaCell.h"

ASeaCell::ASeaCell()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASeaCell::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASeaCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ECellState ASeaCell::GetCellState() const
{
	return _State;
}

ASeaField* ASeaCell::GetParentField() const
{
	return _ParentField;
}

FIntPoint ASeaCell::GetID() const
{
	return _ID;
}

void ASeaCell::SetCellState(ECellState NewState)
{
	_State = NewState;
}

void ASeaCell::SetParentField(ASeaField* ParentPtr)
{
	_ParentField = ParentPtr;
}

bool ASeaCell::SetID(FIntPoint NewID)
{
	if (NewID.X < 0 || NewID.Y < 0)
	{
		UE_LOG(LogSeaField, Error, TEXT("Incorrect ID. ( SeaCell.cpp | bool ASeaCell::SetID(FIntPoint) )"))
		return false;
	}
	_ID = NewID;
	return true;
}