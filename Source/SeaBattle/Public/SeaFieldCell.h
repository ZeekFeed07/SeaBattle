// Copyright (c) 2024 Azizkhon Ishanov. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
/*XXXXXXXXXXXXXXXXXXXXX Include above XXXXXXXXXXXXXXXXXXXXXXXXX*/
#include "SeaFieldCell.generated.h"

UCLASS()
class SEABATTLE_API ASeaFieldCell : public AActor
{
	GENERATED_BODY()
	
public:	
	ASeaFieldCell();

protected:
	virtual void BeginPlay() override;

	FVector _Size;
public:
	virtual void Tick(float DeltaTime) override;


	FVector GetSize() const;
};
