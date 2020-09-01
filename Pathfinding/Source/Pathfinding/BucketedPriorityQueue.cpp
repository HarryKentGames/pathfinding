//#include "BucketedPriorityQueue.h"
//
//template <class T>
//UBucketedPriorityQueue<T>::UBucketedPriorityQueue()
//{
//}
//
//template <class T>
//UBucketedPriorityQueue<T>::~UBucketedPriorityQueue<T>()
//{
//}
//
//template <class T>
//bool UBucketedPriorityQueue<T>::AddElement(T* id, float value)
//{
//	if (queue.Contains(value))
//	{
//		queue[value].Add(id);
//		valueMap.Add(id, value);
//		recordMap.Add(id->node, id);
//	}
//	else
//	{
//		queue.Add(value, Bucket());
//		queue[value].Add(id);
//		valueMap.Add(id, value);
//		recordMap.Add(id->node, id);
//	}
//	queue.KeySort([](float A, float B) {
//		return A < B;
//	});
//	return true;
//}
//
//template <class T>
//bool UBucketedPriorityQueue<T>::RemoveElement(T* id)
//{
//	if (!Contains(id))
//	{
//		return false;
//	}
//	
//	float value = valueMap[id];
//	if (queue.Contains(value) && queue[value].Contains(id))
//	{
//		queue[value].Remove(id);
//		valueMap.Remove(id);
//		recordMap.Remove(id->node);
//
//		if (queue[value].begin() == queue[value].end())
//		{
//			queue.Remove(value);
//		}
//	}
//
//	return true; //Element succesfully removed:
//}
//
//template <class T>
//bool UBucketedPriorityQueue<T>::ModifyElement(T* id, float oldValue, float newValue)
//{
//	Bucket* bucket = queue.Find(oldValue);
//	if (bucket == nullptr)
//	{
//		return false; //Element not found.
//	}
//
//	RemoveElement(id);
//
//	return AddElement(id, newValue);
//}
//
//template <class T>
//bool UBucketedPriorityQueue<T>::GetSmallestElement(T** pId)
//{
//	if (queue.begin() == queue.end())
//	{
//		return false; //Queue is empty.
//	}
//
//	const Bucket& bucket = queue.begin().Value();
//
//	if (bucket.begin() == bucket.end())
//	{
//		return false; //Bucket is empty.
//	}
//
//	*pId = *bucket.begin();
//
//	return true; //Succesfully got smallest value.
//}
//
//template <class T>
//bool UBucketedPriorityQueue<T>::IsEmpty() const
//{
//	return queue.begin() == queue.end();
//}
//
//template <class T>
//bool UBucketedPriorityQueue<T>::Contains(T* id)
//{
//	return valueMap.Contains(id);
//}
//
//template <class T>
//bool UBucketedPriorityQueue<T>::ContainsByNode(const UGraphNode* node)
//{
//	return recordMap.Contains(node);
//}
//
//template <class T>
//bool UBucketedPriorityQueue<T>::FindByNode(T** pId, const UGraphNode* node)
//{
//	if (!ContainsByNode(node))
//	{
//		return false;
//	}
//	else
//	{
//		*pId = recordMap[node];
//		return true;
//	}
//}
//
//template <class T>
//void UBucketedPriorityQueue<T>::Clear()
//{
//	valueMap.Empty();
//	queue.Empty();
//}
