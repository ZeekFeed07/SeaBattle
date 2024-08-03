// Copyright (c) 2024 Azizkhon Ishanov. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root for full license information.


#include "DefaultGamePawn.h"

ADefaultGamePawn::ADefaultGamePawn()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ADefaultGamePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADefaultGamePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADefaultGamePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

