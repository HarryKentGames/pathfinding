#include "AStarNodeRecord.h"

UAStarNodeRecord::UAStarNodeRecord()
{
};

UAStarNodeRecord* UAStarNodeRecord::MAKE(UGraphNode* node, UAStarNodeRecord* connectedNode, float costSoFar, float estimatedTotalCost)
{
	UAStarNodeRecord* record = NewObject<UAStarNodeRecord>();
	record->Init(node, connectedNode, costSoFar, estimatedTotalCost);
	return record;
};

void UAStarNodeRecord::Init(UGraphNode* nodeValue, UAStarNodeRecord* connectedNodeValue, float costSoFarValue, float estimatedTotalCostValue)
{
	node = nodeValue;
	connectedNode = connectedNodeValue;
	costSoFar = costSoFarValue;
	estimatedTotalCost = estimatedTotalCostValue;
};