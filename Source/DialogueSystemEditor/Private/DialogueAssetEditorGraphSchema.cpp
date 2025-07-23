#include "DialogueAssetEditorGraphSchema.h"
#include "DialogueAssetEditorGraphNode.h"

void UDialogueAssetEditorGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& InContextMenuBuilder) const
{
	TSharedPtr<FNewNodeAction> NewNodeAction
	(
		new FNewNodeAction
		(
			FText::FromString(TEXT("Nodes")),
			FText::FromString(TEXT("New node")),
			FText::FromString(TEXT("Makes a new node")),
			0
		)
	);

	InContextMenuBuilder.AddAction(NewNodeAction);
}

FNewNodeAction::FNewNodeAction()
{
}

FNewNodeAction::FNewNodeAction(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, const int32 InGrouping):
	FEdGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping)
{
}

UEdGraphNode* FNewNodeAction::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin,
	const FVector2f& Location, bool bSelectNewNode)
{
	UEdGraphNode* NewNode = NewObject<UDialogueAssetEditorGraphNode>(ParentGraph);
	NewNode->NodePosX = Location.X;
	NewNode->NodePosY = Location.Y;
	ParentGraph->Modify();
	ParentGraph->AddNode(NewNode, true, true);

	return NewNode;
}