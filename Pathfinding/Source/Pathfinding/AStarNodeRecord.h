#pragma once

#include "CoreMinimal.h"
#include "GraphNode.h"
#include "UObject/NoExportTypes.h"
#include "AStarNodeRecord.generated.h"

UCLASS()
class PATHFINDING_API UAStarNodeRecord : public UObject
{
	GENERATED_BODY()
public:
	UGraphNode* node;
	UAStarNodeRecord* connectedNode;
	float costSoFar;
	float estimatedTotalCost;

	UAStarNodeRecord();

	static UAStarNodeRecord* MAKE(UGraphNode* node, UAStarNodeRecord* connectedNode, float costSoFar, float estimatedTotalCost);
	void Init(UGraphNode* nodeValue, UAStarNodeRecord* connectedNodeValue, float costSoFarValue, float estimatedTotalCostValue);
};
