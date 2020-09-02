#include "DijkstraNodeRecord.h"

UDijkstraNodeRecord::UDijkstraNodeRecord()
{
};

UDijkstraNodeRecord* UDijkstraNodeRecord::MAKE(UGraphNode* node, UDijkstraNodeRecord* connectedNode, float costSoFar)
{
	UDijkstraNodeRecord* record = NewObject<UDijkstraNodeRecord>();
	record->Init(node, connectedNode, costSoFar);
	return record;
};

void UDijkstraNodeRecord::Init(UGraphNode* nodeValue, UDijkstraNodeRecord* connectedNodeValue, float costSoFarValue)
{
	node = nodeValue;
	connectedNode = connectedNodeValue;
	costSoFar = costSoFarValue;
};
