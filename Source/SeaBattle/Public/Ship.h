// Copyright (c) 2024 Azizkhon Ishanov. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ship.generated.h"

UCLASS()
class SEABATTLE_API AShip : public AActor
{
	GENERATED_BODY()
	
public:	
	AShip();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual int32 GetShipSize() const;

	UFUNCTION(BlueprintCallable)
	virtual void SetShipSize(int32 NewSize = 1);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Properties", meta = (ExposeOnSpawn = true))
	int32 _Size = 1;
};
