// Copyright (c) 2025 Azizkhon Ishanov. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#include "MainFunctionLibrary.h"

FIntPoint UMainFunctionLibrary::DirToPoint(EShipDirection Dir)
{
	switch (Dir)
	{
	case EShipDirection::LEFT:
		return FIntPoint(-1, 0);
		break;
	case EShipDirection::BOTTOM:
		return FIntPoint(0, -1);
		break;
	case EShipDirection::RIGHT:
		return FIntPoint(1, 0);
		break;
	case EShipDirection::TOP:
		return FIntPoint(0, 1);
		break;
	default:
		return FIntPoint(999, 999);
		break;
	}
}

int32 UMainFunctionLibrary::ShipLengthToNum(EShipLength Length)
{
	return static_cast<int32>(Length) + 1;
}