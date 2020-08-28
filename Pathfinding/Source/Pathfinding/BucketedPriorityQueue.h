#pragma once

#include "CoreMinimal.h"
#include "AStarNodeRecord.h"
#include "UObject/NoExportTypes.h"
#include "BucketedPriorityQueue.generated.h"


typedef TSet<UAStarNodeRecord*> Bucket;
typedef TMap<float, Bucket> Queue;
typedef TMap<UAStarNodeRecord*, float> ValueMap;
typedef TMap<const UGraphNode*, UAStarNodeRecord*> RecordMap;

UCLASS()
class PATHFINDING_API UBucketedPriorityQueue : public UObject
{
	GENERATED_BODY()

public:
    UBucketedPriorityQueue();
    ~UBucketedPriorityQueue();

    bool AddElement(UAStarNodeRecord* id, float value);
    bool RemoveElement(UAStarNodeRecord* id);
    bool ModifyElement(UAStarNodeRecord* id, float oldValue, float newValue);

    bool GetSmallestElement(UAStarNodeRecord** pId);

    bool IsEmpty() const;
    bool Contains(UAStarNodeRecord* id);
    bool ContainsByNode(const UGraphNode* node);
    bool FindByNode(UAStarNodeRecord** pId, const UGraphNode* node);
    void Clear();

private:
    Queue queue;
    ValueMap valueMap;
    RecordMap recordMap;
};
