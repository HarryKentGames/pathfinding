#include "SPathfindingMenuWidget.h"
#include "PathfindingController.h"

#define LOCTEXT_NAMESPACE "Menu"

void SPathfindingMenuWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	OwningHUD = InArgs._OwningHUD;

	const FMargin contentPadding = FMargin(10.0f, 10.0f);
	const FMargin buttonPadding = FMargin(10.0f);

	const FText menuTitleText = LOCTEXT("MenuTitle", "Menu:");

	FSlateFontInfo buttonTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	buttonTextStyle.Size = 15.0f;

	FSlateFontInfo titleTextStyle = buttonTextStyle;
	titleTextStyle.Size = 20.0f;

	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Top)
		.Padding(contentPadding)
		[
			SNew(SVerticalBox)

			+ SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.Font(titleTextStyle)
				.Text(menuTitleText)
				.Justification(ETextJustify::Center)
			]
			
			+ SVerticalBox::Slot()
			[
				SNew(SNumericEntryBox<int32>)
				.Value(this, &SPathfindingMenuWidget::GetStartIndex)
				.OnValueChanged(this, &SPathfindingMenuWidget::SetStartIndex)
			]

			+ SVerticalBox::Slot()
			[
				SNew(SNumericEntryBox<int32>)
				.Value(this, &SPathfindingMenuWidget::GetEndIndex)
				.OnValueChanged(this, &SPathfindingMenuWidget::SetEndIndex)
			]

			+ SVerticalBox::Slot()
			.Padding(buttonPadding)
			[
				SNew(SButton)
				.OnClicked(this, &SPathfindingMenuWidget::ToggleAlgorithmVisualiser)
				[
					SNew(STextBlock)
					.Font(buttonTextStyle)
					.Text(this, &SPathfindingMenuWidget::GetAlgorithmButtonText)
					.Justification(ETextJustify::Center)
				]
			]

			+ SVerticalBox::Slot()
				.Padding(buttonPadding)
				[
					SNew(SButton)
					.OnClicked(this, &SPathfindingMenuWidget::ToggleView)
				[
					SNew(STextBlock)
					.Font(buttonTextStyle)
				.Text(this, &SPathfindingMenuWidget::GetViewButtonText)
				.Justification(ETextJustify::Center)
				]
				]

			+ SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.Font(titleTextStyle)
				.Text(this, &SPathfindingMenuWidget::GetAStarTimeTaken)
				.Justification(ETextJustify::Center)
			]

			+ SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.Font(titleTextStyle)
				.Text(this, &SPathfindingMenuWidget::GetAStarPathLength)
				.Justification(ETextJustify::Center)
			]

			+ SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.Font(titleTextStyle)
				.Text(this, &SPathfindingMenuWidget::GetAStarVisitedNodeCount)
				.Justification(ETextJustify::Center)
			]

			+ SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.Font(titleTextStyle)
				.Text(this, &SPathfindingMenuWidget::GetDijkstraTimeTaken)
				.Justification(ETextJustify::Center)
			]

			+ SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.Font(titleTextStyle)
				.Text(this, &SPathfindingMenuWidget::GetDijkstraPathLength)
				.Justification(ETextJustify::Center)
			]

			+ SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.Font(titleTextStyle)
				.Text(this, &SPathfindingMenuWidget::GetDijkstraVisitedNodeCount)
				.Justification(ETextJustify::Center)
			]
		]
	];
}

void SPathfindingMenuWidget::SetStartIndex(int32 index)
{
	if (startIndex != index)
	{
		startIndex = index;
		OnNodeChanged();
	}
}

TOptional<int32> SPathfindingMenuWidget::GetStartIndex() const
{
	return startIndex;
}

void SPathfindingMenuWidget::SetEndIndex(int32 index)
{
	if (endIndex != index)
	{
		endIndex = index;
		OnNodeChanged();
	}
}

TOptional<int32> SPathfindingMenuWidget::GetEndIndex() const
{
	return endIndex;
}

void SPathfindingMenuWidget::OnNodeChanged() const
{
	if (OwningHUD.IsValid())
	{
		if (UPathfindingController* pathfindingController = OwningHUD->pathfindingController)
		{
			pathfindingController->RunPathfinding(startIndex, endIndex);
		}
	}
}

FText SPathfindingMenuWidget::GetAStarTimeTaken() const
{
	if (OwningHUD.IsValid())
	{
		if (UPathfindingController* pathfindingController = OwningHUD->pathfindingController)
		{
			return FText::Format(NSLOCTEXT("PathfindingMenu", "A*TimeTaken", "A* Time Taken: {0}"), FText::AsNumber(pathfindingController->aStarDebugInfo.timeTaken));
		}
	}
	return FText();
}

FText SPathfindingMenuWidget::GetAStarPathLength() const
{
	if (OwningHUD.IsValid())
	{
		if (UPathfindingController* pathfindingController = OwningHUD->pathfindingController)
		{
			return FText::Format(NSLOCTEXT("PathfindingMenu", "A*PathLength", "A* Path Length: {0}"), FText::AsNumber(pathfindingController->CalculatePathLength(pathfindingController->aStarDebugInfo.path)));
		}
	}
	return FText();
}

FText SPathfindingMenuWidget::GetAStarVisitedNodeCount() const
{
	if (OwningHUD.IsValid())
	{
		if (UPathfindingController* pathfindingController = OwningHUD->pathfindingController)
		{
			return FText::Format(NSLOCTEXT("PathfindingMenu", "A*NodesVisited", "A* Nodes Visited: {0}"), FText::AsNumber(pathfindingController->aStarDebugInfo.visitedNodes.Num()));
		}
	}
	return FText();
}

FText SPathfindingMenuWidget::GetDijkstraTimeTaken() const
{
	if (OwningHUD.IsValid())
	{
		if (UPathfindingController* pathfindingController = OwningHUD->pathfindingController)
		{
			return FText::Format(NSLOCTEXT("PathfindingMenu", "DijkstraTimeTaken", "Dijkstra Time Taken: {0}"), FText::AsNumber(pathfindingController->dijkstraDebugInfo.timeTaken));
		}
	}
	return FText();
}

FText SPathfindingMenuWidget::GetDijkstraPathLength() const
{
	if (OwningHUD.IsValid())
	{
		if (UPathfindingController* pathfindingController = OwningHUD->pathfindingController)
		{
			return FText::Format(NSLOCTEXT("PathfindingMenu", "DijkstraPathLength", "Dijkstra Path Length: {0}"), FText::AsNumber(pathfindingController->CalculatePathLength(pathfindingController->dijkstraDebugInfo.path)));
		}
	}
	return FText();
}

FText SPathfindingMenuWidget::GetDijkstraVisitedNodeCount() const
{
	if (OwningHUD.IsValid())
	{
		if (UPathfindingController* pathfindingController = OwningHUD->pathfindingController)
		{
			return FText::Format(NSLOCTEXT("PathfindingMenu", "DijkstraNodesVisited", "Dijkstra Nodes Visited: {0}"), FText::AsNumber(pathfindingController->dijkstraDebugInfo.visitedNodes.Num()));
		}
	}
	return FText();
}

FReply SPathfindingMenuWidget::ToggleAlgorithmVisualiser()
{
	if (OwningHUD.IsValid())
	{
		if (UPathfindingController* pathfindingController = OwningHUD->pathfindingController)
		{
			pathfindingController->currentDebugInfo = pathfindingController->currentDebugInfo == &pathfindingController->dijkstraDebugInfo ? &pathfindingController->aStarDebugInfo : &pathfindingController->dijkstraDebugInfo;
		}
	}
	return FReply::Handled();
}

FText SPathfindingMenuWidget::GetAlgorithmButtonText() const
{
	if (OwningHUD.IsValid())
	{
		if (UPathfindingController* pathfindingController = OwningHUD->pathfindingController)
		{
			return pathfindingController->currentDebugInfo == &pathfindingController->dijkstraDebugInfo ? FText::FromString("Switch to A*") : FText::FromString("Switch to Dijkstras");
		}
	}
	return FText();
}

FReply SPathfindingMenuWidget::ToggleView()
{
	if (OwningHUD.IsValid())
	{
		if (UPathfindingController* pathfindingController = OwningHUD->pathfindingController)
		{
			pathfindingController->debugView = pathfindingController->debugView == DebugView::Path ? DebugView::Visited : DebugView::Path;
		}
	}
	return FReply::Handled();
}

FText SPathfindingMenuWidget::GetViewButtonText() const
{
	if (OwningHUD.IsValid())
	{
		if (UPathfindingController* pathfindingController = OwningHUD->pathfindingController)
		{
			return pathfindingController->debugView == DebugView::Path ? FText::FromString("View Visited Nodes") : FText::FromString("View Path Found");
		}
	}
	return FText();
}
