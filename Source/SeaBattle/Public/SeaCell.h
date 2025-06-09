// Copyright (c) 2025 Azizkhon Ishanov. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Declarations.h"
#include "SeaCell.generated.h"

class ASeaField;

UENUM(BlueprintType)
enum class ECellState : uint8
{
	CLEAR,
	SHIP,
	DEADZONE
};

UCLASS()
class SEABATTLE_API ASeaCell : public AActor
{
	GENERATED_BODY()

public:
	ASeaCell();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	ECellState GetCellState() const;

	UFUNCTION(BlueprintCallable)
	ASeaField* GetParentField() const;

	UFUNCTION(BlueprintCallable)
	FIntPoint GetID() const;

	void SetCellState(ECellState NewState);

	void SetParentField(ASeaField* ParentPtr);

	bool SetID(FIntPoint NewID);

	UFUNCTION(BlueprintImplementableEvent)
	void Colorize(ECellState State);
	UFUNCTION(BlueprintImplementableEvent)
	void ColorizeWarning();

protected:
	virtual void BeginPlay() override;

private:
	ASeaField* _ParentField = nullptr;

	ECellState _State = ECellState::CLEAR;

	FIntPoint _ID = FIntPoint(-1, -1);
};
