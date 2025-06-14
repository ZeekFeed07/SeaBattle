#pragma once

#include "CoreMinimal.h"

//#define DEBUG_SHIP_PLACING

DECLARE_LOG_CATEGORY_EXTERN(LogSeaField, All, All)


UENUM(BlueprintType)
enum class ECellState : uint8
{
	CLEAR,
	SHIP,
	DEADZONE
};