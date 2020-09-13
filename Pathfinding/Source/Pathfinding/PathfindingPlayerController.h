#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PathfindingPlayerController.generated.h"

UCLASS()
class PATHFINDING_API APathfindingPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	APathfindingPlayerController();
	virtual void SetupInputComponent() override;

	void OpenMenu();
};
