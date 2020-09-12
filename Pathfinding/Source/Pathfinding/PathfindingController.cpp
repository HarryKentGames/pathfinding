#include "PathfindingController.h"

UPathfindingController::UPathfindingController()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPathfindingController::BeginPlay()
{
	Super::BeginPlay();
	graphController = this->GetOwner()->FindComponentByClass<UGraphNodeNetwork>();
	graph = graphController->CreateNetwork();
	float aStarDuration;
	float dijkstrasDuration;
	if (startIndex >= 0 && startIndex < graph.Num() && endIndex >= 0 && endIndex < graph.Num())
	{
		auto start = std::chrono::high_resolution_clock::now();

		TArray<const UGraphNode*> path = UAStarPathfinder::FindAStarPath(graph, graph[startIndex], graph[endIndex], new EuclideanDistance(graph[endIndex]));
		auto end = std::chrono::high_resolution_clock::now();
		aStarDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		DrawPath(path, FColor(0, 255, 0));
		UE_LOG(LogTemp, Warning, TEXT("AStar time taken: %f"), aStarDuration);
		UE_LOG(LogTemp, Warning, TEXT("AStar path length: %i"), path.Num());

	}
	if (startIndex >= 0 && startIndex < graph.Num() && endIndex >= 0 && endIndex < graph.Num())
	{
		auto start = std::chrono::high_resolution_clock::now();
		TArray<const UGraphNode*> path = UDijkstraPathfinder::FindDijkstraPath(graph, graph[startIndex], graph[endIndex]);
		auto end = std::chrono::high_resolution_clock::now();
		dijkstrasDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		DrawPath(path, FColor(255, 0, 0));
		UE_LOG(LogTemp, Warning, TEXT("Dijkstra time taken: %f"), dijkstrasDuration);
		UE_LOG(LogTemp, Warning, TEXT("Dijkstra path length: %i"), path.Num());
	}
}

void UPathfindingController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPathfindingController::DebugDraw()
{
	FColor blue = FColor(0, 0, 255);
	FColor cyan = FColor(0, 255, 255);

	for (UGraphNode* node : graph)
	{
		DrawDebugPoint(GetWorld(), node->GetCoordinates(), 10, blue, true, 0.0f);
		for (TPair<UGraphNode*, float> neighbour : node->GetNeighbours())
		{
			DrawDebugLine(GetWorld(), node->GetCoordinates(), neighbour.Key->GetCoordinates(), cyan, true, 100.0f);
		}
	}
}

void UPathfindingController::DrawPath(TArray<const UGraphNode*> path, FColor color)
{

	//Display all the nodes on the map, with colours representing their influence values:
	for (int i = 0; i < path.Num(); i++)
	{
		DrawDebugPoint(GetWorld(), path[i]->GetCoordinates(), 10, color, true, 100.0f);
		if (i < path.Num() - 1)
		{
			DrawDebugLine(GetWorld(), path[i]->GetCoordinates(), path[i + 1]->GetCoordinates(), color, true, 100.0f);
		}
	}
}

