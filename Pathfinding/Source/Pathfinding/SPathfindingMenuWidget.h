#pragma once

#include "PathfindingHUD.h"
#include "SlateBasics.h"
#include "SlateExtras.h"

class PATHFINDING_API SPathfindingMenuWidget : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SPathfindingMenuWidget) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class APathfindingHUD>, OwningHUD)

	SLATE_END_ARGS()

	TWeakObjectPtr<class APathfindingHUD> OwningHUD;

	void Construct(const FArguments& InArgs);

	virtual bool SupportsKeyboardFocus() const override
	{
		return true;
	}

	int32 startIndex = 0;
	int32 endIndex = 0;

	void SetStartIndex(int32 index);
	TOptional<int32> GetStartIndex() const;
	void SetEndIndex(int32 index);
	TOptional<int32> GetEndIndex() const;

	void OnNodeChanged() const;

	FText GetAStarTimeTaken() const;
	FText GetAStarPathLength() const;
	FText GetAStarVisitedNodeCount() const;

	FText GetDijkstraTimeTaken() const;
	FText GetDijkstraPathLength() const;
	FText GetDijkstraVisitedNodeCount() const;

	FReply ToggleAlgorithmVisualiser();
	FText GetAlgorithmButtonText() const;
	FReply ToggleView();
	FText GetViewButtonText() const;
};
