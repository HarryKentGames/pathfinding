#include "AStarPathfinder.h"

UAStarPathfinder::UAStarPathfinder()
{
}

UAStarPathfinder::~UAStarPathfinder()
{
}

TArray<const UGraphNode*> UAStarPathfinder::FindAStarPath(TArray<UGraphNode*> graph, UGraphNode* start, UGraphNode* end, Heuristic heuristic)
{
	//Initialise the record for the starting node:
	UAStarNodeRecord* startRecord = UAStarNodeRecord::MAKE(start, nullptr, 0.0f, 0.0f);
	//Initialise the necessary data structures:
	UBucketedPriorityQueue* open = NewObject<UBucketedPriorityQueue>();
	UBucketedPriorityQueue* closed = NewObject<UBucketedPriorityQueue>();
	open->AddElement(startRecord, 0);
	UAStarNodeRecord* currentRecord = NewObject<UAStarNodeRecord>();
	//Process each node that is added to the open array:
	while (!open->IsEmpty())
	{
		//Get the best estimated node:
		open->GetSmallestElement(&currentRecord);
		//If it is the goal, stop the algorithm:
		if (currentRecord->node == end)
		{
			break;
		}
		//Loop over all of its neighbours:
		for (TPair<UGraphNode*, float> connectedNode : currentRecord->node->GetNeighbours())
		{
			if (connectedNode.Key == currentRecord->node)
			{
				continue;
			}
			//Get the cost estimate for the neighbour:
			float connectedNodeCost = currentRecord->costSoFar + connectedNode.Value;
			UAStarNodeRecord* connectedNodeRecord = NewObject<UAStarNodeRecord>();
			float connectedNodeHeuristic;
			//If the node has been closed:
			//Skip if the new distance is not less than the current distance
			//remove the entry if it is:
			if (closed->FindByNode(&connectedNodeRecord, connectedNode.Key))
			{
				if (connectedNodeRecord->costSoFar <= connectedNodeCost)
				{
					continue;
				}

				closed->RemoveElement(connectedNodeRecord);

				connectedNodeHeuristic = connectedNodeRecord->estimatedTotalCost - connectedNodeRecord->costSoFar;
			}
			//If the node is open:
			//Skip if the new distance is not less than the current distance
			//Else calculate the new estimated distance:
			else if (open->FindByNode(&connectedNodeRecord, connectedNode.Key))
			{
				if (connectedNodeRecord->costSoFar <= connectedNodeCost)
				{
					continue;
				}

				connectedNodeHeuristic = connectedNodeRecord->estimatedTotalCost - connectedNodeRecord->costSoFar;
			}
			//Else the node is unvisited and needs to be added to the open queue:
			else
			{
				connectedNodeRecord->node = connectedNode.Key;
				connectedNodeHeuristic = heuristic.Estimate(connectedNodeRecord->node);
			}
			float oldEstimatedCost = connectedNodeRecord->estimatedTotalCost;
			//Update the values associated with the record:
			connectedNodeRecord->costSoFar = connectedNodeCost;
			connectedNodeRecord->connectedNode = currentRecord;
			connectedNodeRecord->estimatedTotalCost = connectedNodeCost + connectedNodeHeuristic;
			//Either add to the open list, or update the bucket that the record is in:
			if (!open->ContainsByNode(connectedNode.Key))
			{
				open->AddElement(connectedNodeRecord, connectedNodeCost + connectedNodeHeuristic);
			}
			else
			{
				open->ModifyElement(connectedNodeRecord, oldEstimatedCost, connectedNodeRecord->estimatedTotalCost);
			}
		}
		//Move the current record to the closed list as it has been analysed:
		open->RemoveElement(currentRecord);
		closed->AddElement(currentRecord, currentRecord->estimatedTotalCost);
	}
	//If the current record is for the end node, there is a valid path, otherwise there is not:
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