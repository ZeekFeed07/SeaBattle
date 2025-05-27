// Copyright (c) 2025 Azizkhon Ishanov. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Declarations.h"
#include "Ship.generated.h"

UENUM(BlueprintType)
enum class EShipDirection : uint8
{
	LEFT,
	BOTTOM,
	RIGHT,
	TOP
};

UENUM(BlueprintType)
enum class EShipLength : uint8
{
	ONE,
	TWO,
	THREE,
	FOUR
};

UCLASS()
class SEABATTLE_API AShip : public AActor
{
	GENERATED_BODY()

public:
	AShip();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	EShipLength GetShipLength() const;

	UFUNCTION(BlueprintCallable)
	EShipDirection GetShipDirection() const;

	UFUNCTION(BlueprintCallable)
	bool IsPlaced() const;

	UFUNCTION(BlueprintCallable)
	void SetShipLength(EShipLength NewLength);
	
	UFUNCTION(BlueprintCallable)
	void SetShipDirection(EShipDirection NewDirection);

	UFUNCTION(BlueprintCallable)
	void SetPlacedShip();

	UFUNCTION(BlueprintCallable)
	void SetUnplacedShip();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnLengthChanged();

	UFUNCTION(BlueprintImplementableEvent)
	void OnDirectionChanged();

private:
	EShipLength _Length = EShipLength::ONE;

	EShipDirection _Direction = EShipDirection::TOP;

	bool _bPlaced = false;
};
