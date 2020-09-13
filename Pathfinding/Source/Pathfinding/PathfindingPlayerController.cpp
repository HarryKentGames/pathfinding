#include "PathfindingPlayerController.h"
#include "PathfindingHUD.h"

APathfindingPlayerController::APathfindingPlayerController()
{

}

void APathfindingPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputComponent)
	{
		InputComponent->BindAction("OpenMenu", IE_Pressed, this, &APathfindingPlayerController::OpenMenu);
	}
}

void APathfindingPlayerController::OpenMenu()
{
	if (APathfindingHUD* pathfindingHUD = Cast<APathfindingHUD>(GetHUD()))
	{
		pathfindingHUD->ShowMenu();
	}
}
