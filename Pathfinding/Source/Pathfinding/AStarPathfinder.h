#pragma once

#include "CoreMinimal.h"
#include "BucketedPriorityQueue.h"
#include "UObject/NoExportTypes.h"
#include "AStarPathfinder.generated.h"

class Heuristic
{
public:
	const UGraphNode* endNode;

	Heuristic(const UGraphNode* endNode)
		: endNode(endNode)
	{
	};

	virtual float Estimate(const UGraphNode* node)
	{
		return 0.0f;
	};
};

class EuclideanDistance : public Heuristic
{
public:
	EuclideanDistance(const UGraphNode* endNode)
		: Heuristic(endNode)
	{
	};

	float Estimate(const UGraphNode* node) override
	{
		FVector nodeCoordinates = node->GetCoordinates();
		FVector endCoordinates = endNode->GetCoordinates();
		return sqrt(pow(nodeCoordinates.X - endCoordinates.X, 2) + pow(nodeCoordinates.Y - endCoordinates.Y, 2) + pow(nodeCoordinates.Z - endCoordinates.Z, 2));
	}
};

UCLASS()
class PATHFINDING_API UAStarPathfinder : public UObject
{
	GENERATED_BODY()

public:
	UAStarPathfinder();
	~UAStarPathfinder();

	static TArray<const UGraphNode*> FindAStarPath(TArray<UGraphNode*> graph, UGraphNode* start, UGraphNode* end, Heuristic heuristic);
	
};
