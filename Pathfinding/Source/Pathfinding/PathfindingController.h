#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "AStarPathfinder.h"
#include <chrono>
#include "DijkstraPathfinder.h"
#include "GraphNodeNetwork.h"
#include "PathfindingController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PATHFINDING_API UPathfindingController : public USceneComponent
{
	GENERATED_BODY()

public:	
	UPathfindingController();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	int startIndex;
	UPROPERTY(EditAnywhere)
	int endIndex;

	UGraphNodeNetwork* graphController;
	TArray<UGraphNode*> graph;

	void DebugDraw();
	void DrawPath(TArray<const UGraphNode*> path, FColor color);
};
