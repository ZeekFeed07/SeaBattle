// Copyright (c) 2025 Azizkhon Ishanov. All rights reserved.
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

void ASeaField::InitField()
{
	_World = GetWorld();
	if (!_World)
	{
		UE_LOG(LogSeaField, Error, TEXT("Incorrect pointer to World. ( SeaField.cpp | ASeaField::InitField() )"))
		return;
	}
	if (!CellClass)
	{
		UE_LOG(LogSeaField, Error, TEXT("Incorrect type of CellClass. ( SeaField.cpp | ASeaField::InitField() )"))
		return;
	}
	if (ResizeField(FieldLengthX, FieldLengthY))
	{

		for (int32 i = 0; i < FieldLengthX; ++i)
		{
			for (int32 j = 0; j < FieldLengthY; ++j)
			{
				FVector SpawnPlace = 
					FVector(GetActorLocation().X + i * _CellSize, GetActorLocation().Y + j * _CellSize, GetActorLocation().Z) 
					- FVector(FieldLengthX * _CellSize, FieldLengthY * _CellSize, 0) / 2
					+ FVector(_CellSize / 2, _CellSize / 2, 0);

				FRotator SpawnRotation = FRotator(0, 0, 0);
				_Field[i][j] = _World->SpawnActor<ASeaCell>(CellClass, SpawnPlace, SpawnRotation);
				_Field[i][j]->SetParentField(this);
				_Field[i][j]->SetID(FIntPoint(i, j));
			}
		}
	}
	else
	{
		UE_LOG(LogSeaField, Error, TEXT("Cannot resize field. ( SeaField.cpp | ASeaField::InitField() )"))
	}

	PrintFieldInLog();
}

bool ASeaField::ResizeField(int32 NewSizeX, int32 NewFieldLengthY)
{
	if (NewSizeX < 1)
	{
		UE_LOG(LogSeaField, Error, TEXT("NewSizeX < 1. ( SeaField.cpp | ASeaField::ResizeField(int32, int32) )"))
		return false;
	}
	if (NewFieldLengthY < 1)
	{
		UE_LOG(LogSeaField, Error, TEXT("NewFieldLengthY < 1. ( SeaField.cpp | ASeaField::ResizeField(int32, int32) )"))
		return false;
	}
	_Field.SetNum(NewSizeX);
	for (int32 i = 0; i < NewFieldLengthY; ++i)
	{
		_Field[i].SetNum(NewFieldLengthY);
	}
	return true;
}

bool ASeaField::AddShip(AShip* ShipToPlace, int32 PositionX, int32 PositionY, EShipDirection NewDir)
{
	if (!ShipToPlace)
	{
		UE_LOG(LogSeaField, Error, TEXT("Incorrect Ship pointer. ( SeaField.cpp | ASeaField::AddShip(AShip*, int32, int32) )"))
		return false;
	}
	if (IsShipPlacable(ShipToPlace, PositionX, PositionY, NewDir))
	{
		int32 Length = UMainFunctionLibrary::ShipLengthToNum(ShipToPlace->GetShipLength());
		FIntPoint PointDir = UMainFunctionLibrary::DirToPoint(NewDir);

		ShipMap.Add(FIntPoint(PositionX, PositionY), ShipToPlace);

		for (int32 l = 0; l < Length; ++l)
		{
			_Field[PositionX + l * PointDir.X][PositionY + l * PointDir.Y]->SetCellState(ECellState::SHIP);
			_Field[PositionX + l * PointDir.X][PositionY + l * PointDir.Y]->Colorize(ECellState::SHIP);
			for (int32 i = PositionX - 1 + l * PointDir.X; i <= PositionX + 1 + l * PointDir.X; ++i)
			{
				for (int32 j = PositionY - 1 + l * PointDir.Y; j <= PositionY + 1 + l * PointDir.Y; ++j)
				{
					if (i >= 0 && i < FieldLengthX && j >= 0 && j < FieldLengthY && _Field[i][j]->GetCellState() == ECellState::CLEAR)
					{
						_Field[i][j]->SetCellState(ECellState::DEADZONE);
						_Field[i][j]->Colorize(ECellState::DEADZONE);
					}
				}
			}
		}

		ShipToPlace->SetPlacedShip();

		PrintFieldInLog();
		return true;
	}
	return false;
}

bool ASeaField::RemoveShip(AShip* ShipToRemove)
{
	if (!HasShip(ShipToRemove))
	{
		UE_LOG(LogSeaField, Warning, TEXT("Ship is undefined. ( SeaField.cpp | bool ASeaField::RemoveShip(AShip*) )"))
		return false;
	}

	FIntPoint Position = GetShipPlacedCell(ShipToRemove)->GetID();

	int32 ShipLength = UMainFunctionLibrary::ShipLengthToNum(ShipToRemove->GetShipLength());
	FIntPoint ShipPointDir = UMainFunctionLibrary::DirToPoint(ShipToRemove->GetShipDirection());

	int32 LeftEdge = 0, RightEdge = 0, BottomEdge = 0, TopEdge = 0;

	for (int32 l = 0; l < ShipLength; ++l)
	{
		_Field[Position.X + l * ShipPointDir.X][Position.Y + l * ShipPointDir.Y]->SetCellState(ECellState::CLEAR);
		_Field[Position.X + l * ShipPointDir.X][Position.Y + l * ShipPointDir.Y]->Colorize(ECellState::CLEAR);

		LeftEdge   = Position.X - 1 + l * ShipPointDir.X < 0 ? 0 : Position.X - 1 + l * ShipPointDir.X;
		RightEdge  = Position.X + 1 + l * ShipPointDir.X >= FieldLengthX ? FieldLengthX - 1 : Position.X + 1 + l * ShipPointDir.X;
		BottomEdge = Position.Y - 1 + l * ShipPointDir.Y < 0 ? 0 : Position.Y - 1 + l * ShipPointDir.Y;
		TopEdge    = Position.Y + 1 + l * ShipPointDir.Y >= FieldLengthY ? FieldLengthY - 1 : Position.Y + 1 + l * ShipPointDir.Y;
		
		for (int32 i = LeftEdge; i <= RightEdge; ++i)
		{
			for (int32 j = BottomEdge; j <= TopEdge; ++j)
			{
				if (!IsShipAround(i, j) && _Field[i][j]->GetCellState() == ECellState::DEADZONE)
				{
					_Field[i][j]->SetCellState(ECellState::CLEAR);
					_Field[i][j]->Colorize(ECellState::CLEAR);
				}
			}
		}
	}
	ShipMap.Remove(Position);

	ShipToRemove->SetUnplacedShip();

	return true;
}

void ASeaField::Shoot(int32 PositionX, int32 PositionY, bool& IsHit)
{
	if (PositionX < 0 || PositionX >= FieldLengthX || PositionY < 0 || PositionY >= FieldLengthY)
	{
		UE_LOG(LogSeaField, Error, TEXT("Shoot position is out of field bounds. ( SeaField.cpp | void ASeaField::Shoot(int32, int32) )"))
		IsHit = false;
		return;
	}
	
	ECellState PosState = _Field[PositionX][PositionY]->GetCellState();


	if (PosState == ECellState::CLEAR || PosState == ECellState::DEADZONE)
	{
		IsHit = false;
		_Field[PositionX][PositionY]->SetCellState(ECellState::DEADZONE);
		_Field[PositionX][PositionY]->Colorize(ECellState::DEADZONE);
		return;
	}
	else if (PosState == ECellState::SHIP)
	{
		AShip* AttackedShip = GetShipByPoint(PositionX, PositionY);
		if (AttackedShip->GetNumOfDestroyedParts() > 1)
		{
			AttackedShip->DestroyPart();
			IsHit = true;
			_Field[PositionX][PositionY]->SetCellState(ECellState::SHIP);
			_Field[PositionX][PositionY]->Colorize(ECellState::SHIP);
			return;
		}
		else if (AttackedShip->GetNumOfDestroyedParts() == 1)
		{
			AttackedShip->DestroyPart();
			IsHit = true;
			_Field[PositionX][PositionY]->SetCellState(ECellState::SHIP);
			_Field[PositionX][PositionY]->Colorize(ECellState::SHIP);

			for (int32 i = PositionX - 1; i <= PositionX + 1; ++i)
			{
				for (int32 j = PositionY - 1; j <= PositionY + 1; ++j)
				{
					if (i > 0 && j > 0 && i < FieldLengthX && j < FieldLengthY && _Field[i][j]->GetCellState() == ECellState::CLEAR)
					{
						_Field[i][j]->SetCellState(ECellState::DEADZONE);
						_Field[i][j]->Colorize(ECellState::DEADZONE);
					}
				}
			}
			return;
		}
		else
		{
			UE_LOG(LogSeaField, Warning, TEXT("Attacked to not avialable cell. ( SeaField.cpp | bool ASeaField::Shoot(int32, int32) )"))
			return;
		}
	}
	else
	{ 
		UE_LOG(LogSeaField, Warning, TEXT("Ill-conceived option of ECellState. ( SeaField.cpp | bool ASeaField::Shoot(int32, int32) )"))
		return;
	}
}

bool ASeaField::IsShipPlacable(AShip* ShipToPlace, int32 PositionX, int32 PositionY, EShipDirection NewDir) const
{
	if (!IsCorrectShipPlacing(ShipToPlace, PositionX, PositionY))
	{
		return false;
	}

	int32 Length = UMainFunctionLibrary::ShipLengthToNum(ShipToPlace->GetShipLength());
	FIntPoint PointDirection = UMainFunctionLibrary::DirToPoint(NewDir);
	
	if (PositionX + PointDirection.X * (Length - 1) < 0 || PositionX + PointDirection.X * (Length - 1) >= FieldLengthX)
	{
		return false;
	}
	if (PositionY + PointDirection.Y * (Length - 1) < 0 || PositionY + PointDirection.Y * (Length - 1) >= FieldLengthX)
	{
		return false;
	}

	for (int32 l = 0; l < Length; ++l)
	{
		ECellState CurrentState = _Field[PositionX + l * PointDirection.X][PositionY + l * PointDirection.Y]->GetCellState();
		if (CurrentState == ECellState::DEADZONE || CurrentState == ECellState::SHIP)
		{
#ifdef DEBUG_SHIP_PLACING
			GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Red, FString(TEXT("Can't place a ship")));
#endif // DEBUG

			return false;
		}
	}
#ifdef DEBUG_SHIP_PLACING
	GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Green, FString(TEXT("Ship placed")));
#endif // DEBUG

	return true;
}

bool ASeaField::IsCorrectShipPlacing(AShip* ShipToPlace, int32 PositionX, int32 PositionY) const
{
	if (!ShipToPlace)
	{
		UE_LOG(LogSeaField, Error, TEXT("Incorrect Ship pointer. ( SeaField.cpp | bool ASeaField::IsCorrectShipPlacing(AShip*, int32, int32) const )"))
			return false;
	}

	if (PositionX < 0 || PositionX >= FieldLengthX)
	{
		UE_LOG(LogSeaField, Error, TEXT("PositionX is out of range ( SeaField.cpp | bool ASeaField::IsCorrectShipPlacing(AShip*, int32, int32) const )"))
			return false;
	}
	if (PositionY < 0 || PositionY >= FieldLengthY)
	{
		UE_LOG(LogSeaField, Error, TEXT("PositionY is out of range ( SeaField.cpp | bool ASeaField::IsCorrectShipPlacing(AShip*, int32, int32) const )"))
			return false;
	}
	return true;
}

bool ASeaField::IsShipAround(int32 PointX, int32 PointY) const
{
	if (PointX < 0 || PointY < 0 || PointX >= FieldLengthX || PointY >= FieldLengthY)
	{
		UE_LOG(LogSeaField, Error, TEXT("Coordinates is out of range. ( SeaField.cpp |  bool ASeaField::isShipAround(int32, int32) const )"))
			return false;
	}

	int32 LeftEdge   = PointX - 1 < 0 ? 0 : PointX - 1;
	int32 RightEdge  = PointX + 1 >= FieldLengthX ? FieldLengthX - 1: PointX + 1;
	int32 BottomEdge = PointY - 1 < 0 ? 0 : PointY - 1;
	int32 TopEdge    = PointY + 1 >= FieldLengthY ? FieldLengthY - 1: PointY + 1;

	for (int32 i = LeftEdge; i <= RightEdge; ++i)
	{
		for (int32 j = BottomEdge; j <= TopEdge; ++j)
		{
			if (_Field[i][j]->GetCellState() == ECellState::SHIP) return true;
		}
	}
	return false;
}

bool ASeaField::HasShip(AShip* ShipToCheck) const
{
	return static_cast<bool>(ShipMap.FindKey(ShipToCheck));
}

FVector ASeaField::GetCellLocation(int32 PositionX, int32 PositionY) const
{
	return _Field[PositionX][PositionY]->GetActorLocation();
}

ASeaCell* ASeaField::GetShipPlacedCell(AShip* Ship) const
{
	if (!HasShip(Ship))
	{
		UE_LOG(LogSeaField, Warning, TEXT("Ship is undefined. ( SeaField.cpp | FIntPoint ASeaField::GetShipPoint(AShip*) const )"))
		return nullptr;
	}

	FIntPoint Key = *ShipMap.FindKey(Ship);

	return _Field[Key.X][Key.Y];
}

AShip* ASeaField::GetShipByPoint(int32 PositionX, int32 PositionY)
{
	if (PositionX >= 0 && PositionY >= 0 && PositionX < FieldLengthX && PositionY < FieldLengthY)
	{
		return *ShipMap.Find(FIntPoint(PositionX, PositionY));
	}
	return nullptr;
}

void ASeaField::ColorizeArea(AShip* Ship, int32 PositionX, int32 PositionY)
{
	if (IsShipPlacable(Ship, PositionX, PositionY, Ship->GetShipDirection()))
	{
		int32 Length = UMainFunctionLibrary::ShipLengthToNum(Ship->GetShipLength());
		FIntPoint PointDir = UMainFunctionLibrary::DirToPoint(Ship->GetShipDirection());

		for (int32 l = 0; l < Length; ++l)
		{
			_Field[PositionX + l * PointDir.X][PositionY + l * PointDir.Y]->Colorize(ECellState::SHIP);
			for (int32 i = PositionX - 1 + l * PointDir.X; i <= PositionX + 1 + l * PointDir.X; ++i)
			{
				for (int32 j = PositionY - 1 + l * PointDir.Y; j <= PositionY + 1 + l * PointDir.Y; ++j)
				{
					if (i >= 0 && i < FieldLengthX && j >= 0 && j < FieldLengthY && _Field[i][j]->GetCellState() == ECellState::CLEAR)
					{
						_Field[i][j]->Colorize(ECellState::DEADZONE);
					}
				}
			}
		}
	}
	else
	{
		int32 Length = UMainFunctionLibrary::ShipLengthToNum(Ship->GetShipLength());
		FIntPoint PointDir = UMainFunctionLibrary::DirToPoint(Ship->GetShipDirection());

		for (int32 l = 0; l < Length; ++l)
		{
			for (int32 i = PositionX - 1 + l * PointDir.X; i <= PositionX + 1 + l * PointDir.X; ++i)
			{
				for (int32 j = PositionY - 1 + l * PointDir.Y; j <= PositionY + 1 + l * PointDir.Y; ++j)
				{
					if (i >= 0 && i < FieldLengthX && j >= 0 && j < FieldLengthY)
					{
						_Field[i][j]->ColorizeWarning();
					}
				}
			}
		}
	}
}

void ASeaField::UncolorizeArea(AShip* Ship, int32 PositionX, int32 PositionY)
{
	if (!IsCorrectShipPlacing(Ship, PositionX, PositionY)) return;
	int32 Length = UMainFunctionLibrary::ShipLengthToNum(Ship->GetShipLength());
	FIntPoint PointDir = UMainFunctionLibrary::DirToPoint(Ship->GetShipDirection());

	for (int32 l = 0; l < Length; ++l)
	{
		int32 x = PositionX + l * PointDir.X;
		int32 y = PositionY + l * PointDir.Y;

		if (x >= 0 && x < FieldLengthX && y >= 0 && y < FieldLengthY)
		{
			for (int32 i = PositionX - 1 + l * PointDir.X; i <= PositionX + 1 + l * PointDir.X; ++i)
			{
				for (int32 j = PositionY - 1 + l * PointDir.Y; j <= PositionY + 1 + l * PointDir.Y; ++j)
				{
					if (i >= 0 && i < FieldLengthX && j >= 0 && j < FieldLengthY)
					{
						_Field[i][j]->Colorize(_Field[i][j]->GetCellState());
					}
				}
			}
		}
	}
}

void ASeaField::PrintFieldInLog() const
{
	FString Str = " \n";
	for (int32 i = 0; i < FieldLengthX; ++i)
	{
		for (int32 j = 0; j < FieldLengthY; ++j)
		{
			ECellState CurrState = _Field[i][j]->GetCellState();
			switch (CurrState)
			{
			case ECellState::CLEAR:
				Str += "X ";
				break;
			case ECellState::SHIP:
				Str += "@ ";
				break;
			case ECellState::DEADZONE:
				Str += "= ";
				break;
			default:
				break;
			}
		}
		Str += "\n";
	}

	UE_LOG(LogSeaField, Display, TEXT("%s"), *Str)	
}