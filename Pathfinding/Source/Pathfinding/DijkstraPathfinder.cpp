#include "DijkstraPathfinder.h"

UDijkstraPathfinder::UDijkstraPathfinder()
{
}

UDijkstraPathfinder::~UDijkstraPathfinder()
{
}

TArray<const UGraphNode*> UDijkstraPathfinder::FindDijkstraPath(TArray<UGraphNode*> graph, UGraphNode* start, UGraphNode* end, TArray<const UGraphNode*> &visitedNodes)
{
	UDijkstraNodeRecord* startRecord = UDijkstraNodeRecord::MAKE(start, nullptr, 0.0f);

	UBucketedPriorityQueue<UDijkstraNodeRecord>* open = new UBucketedPriorityQueue<UDijkstraNodeRecord>();
	UBucketedPriorityQueue<UDijkstraNodeRecord>* closed = new UBucketedPriorityQueue<UDijkstraNodeRecord>();
	open->AddElement(startRecord, 0);
	UDijkstraNodeRecord* currentRecord = NewObject<UDijkstraNodeRecord>();

	while (!open->IsEmpty())
	{
		open->GetSmallestElement(&currentRecord);

		if (currentRecord->node == end)
		{
			break;
		}

		for (TPair<UGraphNode*, float> connectedNode : currentRecord->node->GetNeighbours())
		{
			if (connectedNode.Key == currentRecord->node)
			{
				continue;
			}
			UDijkstraNodeRecord* connectedNodeRecord = NewObject<UDijkstraNodeRecord>();
			float connectedNodeCost = currentRecord->costSoFar + connectedNode.Value;
			if (closed->FindByNode(&connectedNodeRecord, connectedNode.Key))
			{
				continue;
			}
			else if (open->FindByNode(&connectedNodeRecord, connectedNode.Key))
			{
				if (connectedNodeRecord->costSoFar <= connectedNodeCost)
				{
					continue;
				}
			}
			else
			{
				connectedNodeRecord->node = connectedNode.Key;
			}
			float oldCostSoFar = connectedNodeRecord->costSoFar;
			connectedNodeRecord->connectedNode = currentRecord;
			connectedNodeRecord->costSoFar = connectedNodeCost;

			if (!open->Contains(connectedNodeRecord))
			{
				open->AddElement(connectedNodeRecord, connectedNodeCost);
			}
			else
			{
				open->ModifyElement(connectedNodeRecord, oldCostSoFar, connectedNodeRecord->costSoFar);
			}
		}
		open->RemoveElement(currentRecord);
		closed->AddElement(currentRecord, currentRecord->costSoFar);
		visitedNodes.Add(currentRecord->node);
	}

	if (currentRecord->node != end)
	{
		return TArray<const UGraphNode*>();
	}
	else
	{
		TArray<const UGraphNode*> path;
		//Loop over the found path, adding the nodes in reverse order to form the path in the correct direction:
		while (currentRecord->node != start)
		{
			path.EmplaceAt(0, currentRecord->node);
			currentRecord = currentRecord->connectedNode;
		}
		return path;
	}

}