#pragma once

#include "CoreMinimal.h"
#include "GraphNode.h"
#include "UObject/NoExportTypes.h"
#include "DijkstraNodeRecord.generated.h"

UCLASS()
class PATHFINDING_API UDijkstraNodeRecord : public UObject
{
	GENERATED_BODY()
public:
	UGraphNode* node;
	UDijkstraNodeRecord* connectedNode;
	float costSoFar;

	UDijkstraNodeRecord();

	static UDijkstraNodeRecord* MAKE(UGraphNode* node, UDijkstraNodeRecord* connectedNode, float costSoFar);
	void Init(UGraphNode* nodeValue, UDijkstraNodeRecord* connectedNodeValue, float costSoFarValue);
};
