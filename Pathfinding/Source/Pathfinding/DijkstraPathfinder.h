#pragma once

#include "CoreMinimal.h"
#include "BucketedPriorityQueue.h"
#include "DijkstraNodeRecord.h"
#include "UObject/NoExportTypes.h"
#include "DijkstraPathfinder.generated.h"

UCLASS()
class PATHFINDING_API UDijkstraPathfinder : public UObject
{
	GENERATED_BODY()
public:
	UDijkstraPathfinder();
	~UDijkstraPathfinder();

	static TArray<const UGraphNode*> FindDijkstraPath(TArray<UGraphNode*> graph, UGraphNode* start, UGraphNode* end);
};
