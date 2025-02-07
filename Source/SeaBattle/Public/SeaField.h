// Copyright (c) 2024 Azizkhon Ishanov. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SeaFieldCell.h"
#include "Ship.h"
/*XXXXXXXXXXXXXXXXXXXXX Include above XXXXXXXXXXXXXXXXXXXXXXXXX*/
#include "SeaField.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSeaField, All, All)

UCLASS()
class SEABATTLE_API ASeaField : public APawn
{
	GENERATED_BODY()

public:
	ASeaField();

protected:
	virtual void BeginPlay() override;

	TArray<TArray<ASeaFieldCell*>> _Field;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Settings")
	int32 LengthX = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Settings")
	int32 LengthY = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Settings")
	float CellGap = 30.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Settings")
	FVector CellSize = FVector(500.f, 500.f, 100.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Settings")
	TSubclassOf<ASeaFieldCell> CellClass;

	/* ===================================== Functions ===================================== */
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Main Settings")
	virtual void InitField();

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Main Settings")
	virtual void ClearField();

	UFUNCTION(BlueprintCallable)
	bool CheckPlace(AShip* ShipPtr, FIntPoint PlacePoint, EShipirection Direction) const;

	UFUNCTION(BlueprintCallable)
	bool CheckPointInField(FIntPoint PointToCheck) const;

	UFUNCTION(BlueprintCallable)
	bool AddShip(AShip* ShipPtr, FIntPoint PlacePoint, EShipirection Direction);

	UFUNCTION(BlueprintCallable)
	ASeaFieldCell* GetCellByCoord(FIntPoint Coord);

private:
	FIntPoint DirToPoint(EShipirection Dir) const; 
};
	