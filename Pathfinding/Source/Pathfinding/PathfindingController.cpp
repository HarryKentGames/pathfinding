#include "PathfindingController.h"

UPathfindingController::UPathfindingController()
{
	PrimaryComponentTick.bCanEverTick = true;
}

UPathfindingController* UPathfindingController::FindInstanceInWorld(UWorld* world)
{
	//Get all the actors in the current world:
	TArray<AActor*> actors = TArray<AActor*>();
	UGameplayStatics::GetAllActorsOfClass(world, AActor::StaticClass(), actors);
	//Find the actor that has an influence map controller attached to it:
	AActor** actor = actors.FindByPredicate([](AActor*& item)
	{
		return item->FindComponentByClass<UPathfindingController>() != nullptr;
	});
	//Return the influence map controller component:
	return (*actor)->FindComponentByClass<UPathfindingController>();
}

void UPathfindingController::BeginPlay()
{
	Super::BeginPlay();
	graphController = this->GetOwner()->FindComponentByClass<UGraphNodeNetwork>();
	graph = graphController->CreateNetwork();
	currentDebugInfo = &aStarDebugInfo;
	debugView = DebugView::Path;
}

void UPathfindingController::RunPathfinding(int startIndex, int endIndex)
{
	if (startIndex >= 0 && startIndex < graph.Num() && endIndex >= 0 && endIndex < graph.Num())
	{
		auto start = std::chrono::high_resolution_clock::now();

		TArray<const UGraphNode*> visitedNodes = TArray<const UGraphNode*>();
		TArray<const UGraphNode*> path = UAStarPathfinder::FindAStarPath(graph, graph[startIndex], graph[endIndex], new EuclideanDistance(graph[endIndex]), visitedNodes);
		auto end = std::chrono::high_resolution_clock::now();

		aStarDebugInfo.timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		aStarDebugInfo.path = path;
		aStarDebugInfo.visitedNodes = visitedNodes;

		visitedNodes = TArray<const UGraphNode*>();
		start = std::chrono::high_resolution_clock::now();
		path = UDijkstraPathfinder::FindDijkstraPath(graph, graph[startIndex], graph[endIndex], visitedNodes);
		end = std::chrono::high_resolution_clock::now();

		dijkstraDebugInfo.timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		dijkstraDebugInfo.path = path;
		dijkstraDebugInfo.visitedNodes = visitedNodes;
	}
}

float UPathfindingController::CalculatePathLength(TArray<const UGraphNode*> path)
{
	float pathLength = 0.0f;
	for (int i = 0; i < path.Num() - 1; i++)
	{
		pathLength += path[i]->GetNeighbours()[path[i + 1]];
	}
	return pathLength;
}

PathfindingDebugInformation* UPathfindingController::GetAStarDebugInfo()
{
	return &aStarDebugInfo;
}

PathfindingDebugInformation* UPathfindingController::GetDijkstraDebugInfo()
{
	return &dijkstraDebugInfo;
}

void UPathfindingController::SetCurrentDebugInfo(PathfindingDebugInformation* newDebugInfo)
{
	currentDebugInfo = newDebugInfo;
}

PathfindingDebugInformation* UPathfindingController::GetCurrentDebugInfo() const
{
	return currentDebugInfo;
}

void UPathfindingController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (debugView == DebugView::Path)
	{
		DrawNodes(currentDebugInfo->path, FColor(0, 255, 0), true);
	}
	else if (debugView == DebugView::Visited)
	{
		DrawNodes(currentDebugInfo->visitedNodes, FColor(255, 0, 0), false);
	}
}

void UPathfindingController::DrawNodes(TArray<const UGraphNode*> path, FColor color, bool connect)
{
	for (int i = 0; i < path.Num(); i++)
	{
		DrawDebugPoint(GetWorld(), path[i]->GetCoordinates(), 10, color, false, 0.0f);
		if (connect && i < path.Num() - 1)
		{
			DrawDebugLine(GetWorld(), path[i]->GetCoordinates(), path[i + 1]->GetCoordinates(), color, false, 0.0f);
		}
	}
}

