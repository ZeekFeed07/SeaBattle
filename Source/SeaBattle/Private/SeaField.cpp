// Copyright (c) 2024 Azizkhon Ishanov. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#include "SeaField.h"

DEFINE_LOG_CATEGORY(LogSeaField)

ASeaField::ASeaField()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASeaField::BeginPlay()
{
	Super::BeginPlay();
	

}

void ASeaField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASeaField::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASeaField::InitField()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("World is undefined"))
		return;
	}	
	
	if (LengthX < 4 || LengthY < 4)
	{
		UE_LOG(LogSeaField, Error, TEXT("Field not created. Too small length"))
		return;
	}
	ClearField();


	FVector FieldSize = FVector( (CellSize.X + CellGap) * LengthX - CellGap, (CellSize.Y + CellGap) * LengthY - CellGap, CellSize.Z);
	FVector FieldHalfSize = FieldSize / 2;
	FVector CellHalfSize = FVector(CellSize.X / 2, CellSize.Y / 2, CellSize.Z / 2);

	_Field.SetNum(LengthX);
	for (int32 i = 0; i < LengthX; ++i)
	{
		_Field[i].SetNum(LengthY);
		for (int32 j = 0; j < LengthY; ++j)
		{
			FVector PlaceLocation = FVector(i * (CellSize.X + CellGap) - CellGap, j * (CellSize.Y + CellGap) - CellGap, CellSize.Z) + CellHalfSize - FieldHalfSize + CellGap;
			FRotator Rotator = FRotator(0, 0, 0);

			_Field[i][j] = World->SpawnActor<ASeaFieldCell>(CellClass, PlaceLocation, Rotator);
		}
	}
}

void ASeaField::ClearField()
{
	UE_LOG(LogSeaField, Display, TEXT("%d"), _Field.Num())

	for (int32 i = 0; i < _Field.Num(); ++i)
	{
		for (int32 j = 0; j < _Field[i].Num(); ++j)
		{
			_Field[i][j]->Destroy();
		}
		_Field[i].Empty();
	}
	_Field.Empty();

	UE_LOG(LogSeaField, Display, TEXT("%d"), _Field.Num())
}

void ASeaField::AddShip(AShip* ShipPtr, int32 Place_i, int32 Place_j, int32 dir_i, int32 dir_j)
{
}

void ASeaField::CheckPlacement(int32 ShipSize, int32 Place_i, int32 Place_j, int32 dir_i, int32 dir_j)
{
}

