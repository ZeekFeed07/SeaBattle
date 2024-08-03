// Copyright (c) 2024 Azizkhon Ishanov. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
/*XXXXXXXXXXXXXXXXXXXXX Include above XXXXXXXXXXXXXXXXXXXXXXXXX*/
#include "SeaField.generated.h"

UCLASS()
class SEABATTLE_API ASeaField : public APawn
{
	GENERATED_BODY()

public:
	ASeaField();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
