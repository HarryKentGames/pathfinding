#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PathfindingController.h"
#include "PathfindingHUD.generated.h"

UCLASS()
class PATHFINDING_API APathfindingHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPathfindingController* pathfindingController;

	void ShowMenu();
	void RemoveMenu();

protected:
	TSharedPtr<class SPathfindingMenuWidget> MenuWidget;
	TSharedPtr<class SWidget> MenuWidgetContainer;

	virtual void BeginPlay() override;
};
