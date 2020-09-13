// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PathfindingHUD.h"
#include "PathfindingGameModeBase.generated.h"

UCLASS()
class PATHFINDING_API APathfindingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	APathfindingGameModeBase();
	virtual void StartPlay() override;
};
