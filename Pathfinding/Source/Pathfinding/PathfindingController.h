#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "AStarPathfinder.h"
#include <chrono>
#include "DijkstraPathfinder.h"
#include "GraphNodeNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "PathfindingController.generated.h"

struct PathfindingDebugInformation
{
	float timeTaken;
	TArray<const UGraphNode*> visitedNodes;
	TArray<const UGraphNode*> path;
};

UENUM()
enum DebugView
{
	Path     UMETA(DisplayName = "Path"),
	Visited      UMETA(DisplayName = "Visited"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PATHFINDING_API UPathfindingController : public USceneComponent
{
	GENERATED_BODY()

public:	
	UPathfindingController();

	static UPathfindingController* FindInstanceInWorld(UWorld* world);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void RunPathfinding(int startIndex, int endIndex);
	float CalculatePathLength(TArray<const UGraphNode*> path);

	PathfindingDebugInformation aStarDebugInfo;
	PathfindingDebugInformation dijkstraDebugInfo;

	PathfindingDebugInformation* currentDebugInfo;
	TEnumAsByte<DebugView> debugView;

protected:
	virtual void BeginPlay() override;

private:
	UGraphNodeNetwork* graphController;
	TArray<UGraphNode*> graph;

	void DrawPath(TArray<const UGraphNode*> path, FColor color);
};
