#include "DijkstraPathfinder.h"

UDijkstraPathfinder::UDijkstraPathfinder()
{
}

UDijkstraPathfinder::~UDijkstraPathfinder()
{
}

TArray<const UGraphNode*> UDijkstraPathfinder::FindDijkstraPath(TArray<UGraphNode*> graph, UGraphNode* start, UGraphNode* end, TArray<const UGraphNode*> &visitedNodes)
{
	//Initialise the record for the start node:
	UDijkstraNodeRecord* startRecord = UDijkstraNodeRecord::MAKE(start, nullptr, 0.0f);
	//Initialise necessary data structures:
	UBucketedPriorityQueue<UDijkstraNodeRecord>* open = new UBucketedPriorityQueue<UDijkstraNodeRecord>();
	UBucketedPriorityQueue<UDijkstraNodeRecord>* closed = new UBucketedPriorityQueue<UDijkstraNodeRecord>();
	open->AddElement(startRecord, 0);
	UDijkstraNodeRecord* currentRecord = NewObject<UDijkstraNodeRecord>();
	//Process each node in the open list:
	while (!open->IsEmpty())
	{
		//Get the node with the shortest distance:
		open->GetSmallestElement(&currentRecord);
		//If it is the goal, stop:
		if (currentRecord->node == end)
		{
			break;
		}
		//Loop over all its neighbours:
		for (TPair<UGraphNode*, float> connectedNode : currentRecord->node->GetNeighbours())
		{
			if (connectedNode.Key == currentRecord->node)
			{
				continue;
			}
			//Calculate the distance to the neighbour from the start node:
			UDijkstraNodeRecord* connectedNodeRecord = NewObject<UDijkstraNodeRecord>();
			float connectedNodeCost = currentRecord->costSoFar + connectedNode.Value;
			//If the node has already been closed, skip:
			if (closed->FindByNode(&connectedNodeRecord, connectedNode.Key))
			{
				continue;
			}
			//If it is open, but the new route is worse, skip:
			else if (open->FindByNode(&connectedNodeRecord, connectedNode.Key))
			{
				if (connectedNodeRecord->costSoFar <= connectedNodeCost)
				{
					continue;
				}
			}
			//Else it is unvisited, or a better route has been found, update the node:
			else
			{
				connectedNodeRecord->node = connectedNode.Key;
			}
			//Update cost and connection:
			float oldCostSoFar = connectedNodeRecord->costSoFar;
			connectedNodeRecord->connectedNode = currentRecord;
			connectedNodeRecord->costSoFar = connectedNodeCost;
			//Add or modify the record in the open list:
			if (!open->Contains(connectedNodeRecord))
			{
				open->AddElement(connectedNodeRecord, connectedNodeCost);
			}
			else
			{
				open->ModifyElement(connectedNodeRecord, oldCostSoFar, connectedNodeRecord->costSoFar);
			}
		}
		//As all neighbours have been assessed, move to the closed list:
		open->RemoveElement(currentRecord);
		closed->AddElement(currentRecord, currentRecord->costSoFar);
		visitedNodes.Add(currentRecord->node);
	}
	//Reconstruct the path found:
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
		path.EmplaceAt(0, currentRecord->node);
		return path;
	}

}