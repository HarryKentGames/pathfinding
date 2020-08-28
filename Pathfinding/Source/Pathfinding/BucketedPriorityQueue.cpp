#include "BucketedPriorityQueue.h"


UBucketedPriorityQueue::UBucketedPriorityQueue()
{
}

UBucketedPriorityQueue::~UBucketedPriorityQueue()
{
}

bool UBucketedPriorityQueue::AddElement(UAStarNodeRecord* id, float value)
{
	if (queue.Contains(value))
	{
		queue[value].Add(id);
		valueMap.Add(id, value);
		recordMap.Add(id->node, id);
	}
	else
	{
		queue.Add(value, Bucket());
		queue[value].Add(id);
		valueMap.Add(id, value);
		recordMap.Add(id->node, id);
	}
	queue.KeySort([](float A, float B) {
		return A < B;
	});
	return true;
}

bool UBucketedPriorityQueue::RemoveElement(UAStarNodeRecord* id)
{
	if (!Contains(id))
	{
		return false;
	}
	
	float value = valueMap[id];
	if (queue.Contains(value) && queue[value].Contains(id))
	{
		queue[value].Remove(id);
		valueMap.Remove(id);
		recordMap.Remove(id->node);

		if (queue[value].begin() == queue[value].end())
		{
			queue.Remove(value);
		}
	}

	return true; //Element succesfully removed:
}

bool UBucketedPriorityQueue::ModifyElement(UAStarNodeRecord* id, float oldValue, float newValue)
{
	Bucket* bucket = queue.Find(oldValue);
	if (bucket == nullptr)
	{
		return false; //Element not found.
	}

	RemoveElement(id);

	return AddElement(id, newValue);
}

bool UBucketedPriorityQueue::GetSmallestElement(UAStarNodeRecord** pId)
{
	if (queue.begin() == queue.end())
	{
		return false; //Queue is empty.
	}

	const Bucket& bucket = queue.begin().Value();

	if (bucket.begin() == bucket.end())
	{
		return false; //Bucket is empty.
	}

	*pId = *bucket.begin();

	return true; //Succesfully got smallest value.
}

bool UBucketedPriorityQueue::IsEmpty() const
{
	return queue.begin() == queue.end();
}

bool UBucketedPriorityQueue::Contains(UAStarNodeRecord* id)
{
	return valueMap.Contains(id);
}

bool UBucketedPriorityQueue::ContainsByNode(const UGraphNode* node)
{
	return recordMap.Contains(node);
}

bool UBucketedPriorityQueue::FindByNode(UAStarNodeRecord** pId, const UGraphNode* node)
{
	if (!ContainsByNode(node))
	{
		return false;
	}
	else
	{
		*pId = recordMap[node];
		return true;
	}
}

void UBucketedPriorityQueue::Clear()
{
	valueMap.Empty();
	queue.Empty();
}
