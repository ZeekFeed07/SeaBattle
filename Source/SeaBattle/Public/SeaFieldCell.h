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

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetCoord(FIntPoint NewCoord);

	UFUNCTION(BlueprintCallable)
	FIntPoint GetCoord() const;

	UFUNCTION(BlueprintCallable)
	void SetAvialable(bool NewAvialibility);

	UFUNCTION(BlueprintCallable)
	bool GetAvialable() const;

	UFUNCTION(BlueprintCallable)
	void SetHasShip(bool Value);

	UFUNCTION(BlueprintCallable)
	bool GetHasShip() const;

	UFUNCTION(BlueprintCallable)
	FVector GetSize() const;

protected:

	FVector _Size;

	FIntPoint _Coord = FIntPoint(0, 0);

	bool _bAvialable = true;

	bool _bHasShip = false;
};
