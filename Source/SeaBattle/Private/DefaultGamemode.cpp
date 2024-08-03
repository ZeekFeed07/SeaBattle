// Copyright (c) 2024 Azizkhon Ishanov. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#include "DefaultGamemode.h"
#include "DefaultGamePawn.h"
#include "DefaultPlayerController.h"

ADefaultGamemode::ADefaultGamemode()
{
	DefaultPawnClass = ADefaultGamePawn::StaticClass();
	PlayerControllerClass = ADefaultPlayerController::StaticClass();
}