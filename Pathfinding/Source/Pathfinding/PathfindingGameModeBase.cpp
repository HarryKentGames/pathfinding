// Copyright Epic Games, Inc. All Rights Reserved.

#include "PathfindingGameModeBase.h"
#include "PathfindingPlayerController.h"


APathfindingGameModeBase::APathfindingGameModeBase()
{
	HUDClass = APathfindingHUD::StaticClass();
	PlayerControllerClass = APathfindingPlayerController::StaticClass();
};

void APathfindingGameModeBase::StartPlay()
{
	Super::StartPlay();
}
