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
// move the code for visualization to BP class
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
	FVector FieldPos = GetActorLocation();

	_Field.SetNum(LengthX);
	for (int32 i = 0; i < LengthX; ++i)
	{
		_Field[i].SetNum(LengthY);
		for (int32 j = 0; j < LengthY; ++j)
		{
			FVector PlaceLocation = FVector(i * (CellSize.X + CellGap) - CellGap, j * (CellSize.Y + CellGap) - CellGap, CellSize.Z) + CellHalfSize - FieldHalfSize + CellGap + FieldPos;
			FRotator Rotator = FRotator(0, 0, 0);

			_Field[i][j] = World->SpawnActor<ASeaFieldCell>(CellClass, PlaceLocation, Rotator);
			_Field[i][j]->SetCoord(FIntPoint(i, j));
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

/*bool ASeaField::CheckPlace(AShip* ShipPtr, FIntPoint Place, EShipirection Direction) const
{
	if (!ShipPtr)
	{
		UE_LOG(LogSeaField, Error, TEXT("Ship pointer is incorrect. (SeaField.cpp | ASeaField::CheckPlace)"))
		return false;
	}
	int32 ShipSize = ShipPtr->GetShipSize() - 1;
	//int32 PlaceX = Place.X;
	//int32 PlaceY = Place.Y;

	FIntPoint Dir = DirToPoint(Direction);
	//int32 DirX = Dir.X;
	//int32 DirY = Dir.Y;

	//bool expr1 = ( (PlaceX + DirX * ShipSize) <    _Field.Num() ) && ( (PlaceX + DirX * ShipSize) >= 0 );
	//bool expr2 = ( (PlaceY + DirY * ShipSize) < _Field[0].Num() ) && ( (PlaceY + DirY * ShipSize) >= 0 );

	//return expr1 && expr2;
	
	return CheckPointInField(Place + Dir * ShipSize);

}*/


bool ASeaField::CheckPlace(AShip* ShipPtr, FIntPoint PlacePoint, EShipDirection Direction) const
{
	if (!ShipPtr)
	{
		UE_LOG(LogSeaField, Error, TEXT("Ship pointer is incorrect. (SeaField.cpp | ASeaField::CheckPlace)"))
		return false;
	}
	int32 StretchSize = ShipPtr->GetShipSize() - 1;
	FIntPoint Dir = DirToPoint(Direction);

	// Checking if ship in range 
	if (!CheckPointInField(PlacePoint + Dir * StretchSize)) return false;
	// Check cell avialability for placing 
	for (int32 i = 0; i < ShipPtr->GetShipSize(); ++i)
	{
		if (!_Field[PlacePoint.X + Dir.X * i][PlacePoint.Y + Dir.Y * i]->GetAvialable()) return false;
	}
	return true;
}

bool ASeaField::CheckPointInField(FIntPoint PointToCheck) const
{
	// Check Field size
	if ((_Field.Num() < 0) && (_Field[0].Num() < 0))
	{
		UE_LOG(LogSeaField, Error, TEXT("Field is empty. (SeaField.cpp | ASeaField::CheckPointInField)"))
		return false;
	}

	bool expr1 = (PointToCheck.X >= 0) && (PointToCheck.Y >= 0);
	bool expr2 = (PointToCheck.X < _Field.Num()) && (PointToCheck.Y < _Field[0].Num());

	return expr1 && expr2;
}

bool ASeaField::AddShip(AShip* ShipPtr, FIntPoint PlacePoint, EShipDirection Direction)
{
	if (!ShipPtr)
	{
		UE_LOG(LogSeaField, Error, TEXT("Ship pointer is incorrect. (SeaField.cpp | ASeaField::AddShip)"))
		return false;
	}

	if (CheckPlace(ShipPtr, PlacePoint, Direction))
	{
		bool flag = ((Direction == EShipDirection::LEFT) || (Direction == EShipDirection::RIGHT));

		int32 X = flag ? 2 : ShipPtr->GetShipSize() + 1;
		int32 Y = flag ? ShipPtr->GetShipSize() + 1 : 2;

		for (int32 ix = PlacePoint.X - 1; ix < PlacePoint.X + X; ++ix)
		{
			for (int32 jy = PlacePoint.Y - 1; jy < PlacePoint.Y + Y; ++jy)
			{
				if (ix >= 0 && jy >= 0 && ix < LengthX && jy < LengthY)
				{
					_Field[ix][jy]->SetAvialable(false);
				}
			}
		}

		_ShipsList.Push(ShipPtr);
			
		FIntPoint DirId = DirToPoint(Direction);
		for (int32 i = 0; i < ShipPtr->GetShipSize(); ++i)
		{
			_Field[PlacePoint.X + i * DirId.X][PlacePoint.Y + i * DirId.Y]->SetHasShip(true);
		}
		return true;
	}

	return false;
}


ASeaFieldCell* ASeaField::GetCellByCoord(FIntPoint Coord)
{
	if (Coord.X >= 0 && Coord.Y >= 0 && Coord.X < LengthX && Coord.Y < LengthY)
	{
		return _Field[Coord.X][Coord.Y];
	}
	else
	{
		UE_LOG(LogSeaField, Error, TEXT("Coordinated out of field bounds. (SeaField.cpp | ASeaField::GetCellByCoord)"))
		return nullptr;
	}
}

FIntPoint ASeaField::DirToPoint(EShipDirection Dir) const
{	
	switch (Dir)	
	{
	case EShipDirection::LEFT:
		return FIntPoint(0, -1);
		break;
	case EShipDirection::BOTTOM:
		return FIntPoint(-1, 0);
		break;
	case EShipDirection::RIGHT:
		return FIntPoint(0, 1);
		break;
	case EShipDirection::TOP:
		return FIntPoint(1, 0);
		break;
	default:
		return FIntPoint(999, 999);
		break;
	}
}
