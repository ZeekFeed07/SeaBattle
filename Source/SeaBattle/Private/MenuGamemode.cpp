// Copyright (c) 2024 Azizkhon Ishanov. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#include "MenuGamemode.h"
#include "MenuPlayerController.h"
#include "MenuPawn.h"

AMenuGamemode::AMenuGamemode()
{
	PlayerControllerClass = AMenuPlayerController::StaticClass();
	DefaultPawnClass = AMenuPawn::StaticClass();
}