// Copyright (c) 2025 Azizkhon Ishanov. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Declarations.h"
#include "SeaCell.h"
#include "Ship.h"
#include "MainFunctionLibrary.h"

#include "SeaField.generated.h"

UCLASS()
class SEABATTLE_API ASeaField : public AActor
{
	GENERATED_BODY()
	
public:	

	ASeaField();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void InitField();

	virtual bool ResizeField(int32 NewSizeX, int32 NewSizeY);

	UFUNCTION(BlueprintCallable)
	virtual bool AddShip(AShip* ShipToPlace, int32 PositionX, int32 PositionY, EShipDirection NewDir);

	UFUNCTION(BlueprintCallable)
	virtual bool RemoveShip(AShip* ShipToRemove);

	UFUNCTION(BlueprintCallable)
	virtual void Shoot(int32 PositionX, int32 PositionY, bool& IsHit);

	bool IsShipPlacable(AShip* ShipToPlace, int32 PositionX, int32 PositionY, EShipDirection NewDir) const;

	bool IsCorrectShipPlacing(AShip* ShipToPlace, int32 PositionX, int32 PositionY) const;

	bool IsShipAround(int32 PointX, int32 PointY) const;

	UFUNCTION(BluePrintCallable)
	bool HasShip(AShip* ShipToCheck) const;

	UFUNCTION(BlueprintCallable)
	FVector GetCellLocation(int32 PositionX, int32 PositionY) const;

	UFUNCTION(BlueprintCallable)
	FIntPoint GetPointByShip(AShip* Ship) const;

	UFUNCTION(BlueprintCallable)
	AShip* GetShipByPoint(int32 PositionX, int32 PositionY);
	
	UFUNCTION(BlueprintCallable)
	void ColorizeArea(AShip* Ship, int32 PositionX, int32 PositionY);
	UFUNCTION(BlueprintCallable)
	void UncolorizeArea(AShip* Ship, int32 PositionX, int32 PositionY);

	UFUNCTION(BlueprintCallable)
	void PrintFieldInLog() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Settings", meta = (ExposeOnSpawn = "true"))
	TSubclassOf<ASeaCell> CellClass;

protected:
	virtual void BeginPlay() override;

private:

	UWorld* _World = nullptr;

	const int32 FieldLengthX = 10;
	const int32 FieldLengthY = 10;

	float _CellSize		= 500.f;
	float _CellHeight	= 100.f;

	TArray<TArray<ASeaCell*>> _Field = TArray<TArray<ASeaCell*>>();
	TMap<FIntPoint, AShip*> ShipMap = TMap<FIntPoint, AShip*>();
};
