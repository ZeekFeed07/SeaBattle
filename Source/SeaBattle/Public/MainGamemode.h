// Copyright (c) 2024 Azizkhon Ishanov. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Declarations.h"

#include "MainGamemode.generated.h"
	
UCLASS()
class SEABATTLE_API AMainGamemode : public AGameMode
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	bool IsShip(int32 PositionX, int32 PositionY) const;

	UFUNCTION(BlueprintCallable)
	void SetCellState(int32 PositionX, int32 PositionY, ECellState State);

protected:
	virtual void BeginPlay() override;

private:
	int32 FieldLengthX = 10;
	int32 FieldLengthY = 10;

	TArray<TArray<ECellState>> _Temp = TArray<TArray<ECellState>>();
};