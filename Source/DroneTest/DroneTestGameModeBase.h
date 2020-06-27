// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DroneTestGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DRONETEST_API ADroneTestGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	int32 scores;

};
