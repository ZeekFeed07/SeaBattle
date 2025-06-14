// Copyright (c) 2025 Azizkhon Ishanov. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#include "MainGamemode.h"

bool AMainGamemode::IsShip(int32 PositionX, int32 PositionY) const
{
	return _Temp[PositionX][PositionY] == ECellState::SHIP;
}


void AMainGamemode::SetCellState(int32 PositionX, int32 PositionY, ECellState State)
{
	_Temp[PositionX][PositionY] = State;
}

void AMainGamemode::BeginPlay()
{
	Super::BeginPlay();

	_Temp.SetNum(FieldLengthX);

	for (int32 i = 0; i < FieldLengthX; ++i)
	{
		_Temp[i].SetNum(FieldLengthY);
		for (int32 j = 0; j < FieldLengthY; ++j)
		{
			_Temp[i][j] = ECellState::CLEAR;
		}
	}


	_Temp[4][5] = ECellState::DEADZONE;
	_Temp[4][6] = ECellState::DEADZONE;
	_Temp[4][7] = ECellState::DEADZONE;

	_Temp[5][5] = ECellState::DEADZONE;
	_Temp[5][6] = ECellState::SHIP;
	_Temp[5][7] = ECellState::DEADZONE;

	_Temp[6][5] = ECellState::DEADZONE;
	_Temp[6][6] = ECellState::DEADZONE;
	_Temp[6][7] = ECellState::DEADZONE;
}
