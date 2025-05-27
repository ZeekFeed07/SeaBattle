// Copyright (c) 2025 Azizkhon Ishanov. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Ship.h"

#include "MainFunctionLibrary.generated.h"

UCLASS()
class SEABATTLE_API UMainFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
	static FIntPoint DirToPoint(EShipDirection Dir);

	UFUNCTION(BlueprintPure)
	static int32 ShipLengthToNum(EShipLength Length);
};
