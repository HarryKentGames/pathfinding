#pragma once

#include "CoreMinimal.h"
#include "GraphNode.h"
#include "UObject/NoExportTypes.h"

template <class T>
class UBucketedPriorityQueue
{
    using Bucket = TSet<T*>;
    using Queue = TMap<float, Bucket>;
    using ValueMap = TMap<T*, float>;
    using RecordMap = TMap<const UGraphNode*, T*>;
public:
    UBucketedPriorityQueue()
    {
    }

    ~UBucketedPriorityQueue<T>()
    {
    }

    bool AddElement(T* id, float value)
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

    bool RemoveElement(T* id)
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

    bool ModifyElement(T* id, float oldValue, float newValue)
    {
        Bucket* bucket = queue.Find(oldValue);
        if (bucket == nullptr)
        {
            return false; //Element not found.
        }

        RemoveElement(id);

        return AddElement(id, newValue);
    }

    bool GetSmallestElement(T** pId)
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

    bool IsEmpty() const
    {
        return queue.begin() == queue.end();
    }
    
    bool Contains(T* id)
    {
        return valueMap.Contains(id);
    }
    
    bool ContainsByNode(const UGraphNode* node)
    {
        return recordMap.Contains(node);
    }
    
    bool FindByNode(T** pId, const UGraphNode* node)
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
    
    void Clear()
    {
        valueMap.Empty();
        queue.Empty();
    }

private:
    Queue queue;
    ValueMap valueMap;
    RecordMap recordMap;
};
