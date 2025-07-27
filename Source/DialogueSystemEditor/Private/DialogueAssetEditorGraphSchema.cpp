#include "DialogueAssetEditorGraphSchema.h"
#include "DialogueAssetEditorGraphNode.h"
#include "DialogueNodeData.h"

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

const FPinConnectionResponse UDialogueAssetEditorGraphSchema::CanCreateConnection(const UEdGraphPin* InA,
	const UEdGraphPin* InB) const
{
	if (!InA || !InB)
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Invalid pins"));

	if (InA->Direction == InB->Direction)
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Inputs can only connect to outputs"));

	if (InA->GetOwningNode() == InB->GetOwningNode())
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Can't connect to itself"));	

	return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_AB, TEXT(""));
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
	UDialogueAssetEditorGraphNode* NewNode = NewObject<UDialogueAssetEditorGraphNode>(ParentGraph);
	NewNode->NodePosX = Location.X;
	NewNode->NodePosY = Location.Y;
	NewNode->CreateNewGuid();
	NewNode->SetNodeData(NewObject<UDialogueNodeData>(NewNode));

	UEdGraphPin* InputPin = NewNode->CreateDialoguePin(EGPD_Input, TEXT("Display"));
	FString DefaultResponse = TEXT("Response");
	NewNode->CreateDialoguePin(EEdGraphPinDirection::EGPD_Output, FName(DefaultResponse));
	NewNode->GetNodeData()->Responses.Add(FText::FromString(DefaultResponse));

	if (FromPin)
	{
		NewNode->GetSchema()->TryCreateConnection(InputPin, FromPin);
	}

	ParentGraph->Modify();
	ParentGraph->AddNode(NewNode, true, true);

	return NewNode;
}