#include "DialogueAssetEditorGraphSchema.h"
#include "DialogueAssetEditorGraphNodeLine.h"
#include "DialogueAssetEditorGraphNodeStart.h"
#include "DialogueNodeDataLine.h"

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

void UDialogueAssetEditorGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	UDialogueAssetEditorGraphNodeStart* StartNode = NewObject<UDialogueAssetEditorGraphNodeStart>(&Graph);
	StartNode->CreateNewGuid();
	StartNode->NodePosX = 0;
	StartNode->NodePosY = 0;

	StartNode->CreateDialoguePin(EEdGraphPinDirection::EGPD_Output, FName(TEXT("Start")));

	Graph.AddNode(StartNode, true, true);
	Graph.Modify();
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
	UDialogueAssetEditorGraphNodeLine* NewNode = NewObject<UDialogueAssetEditorGraphNodeLine>(ParentGraph);
	NewNode->NodePosX = Location.X;
	NewNode->NodePosY = Location.Y;
	NewNode->CreateNewGuid();
	NewNode->SetNodeData(NewObject<UDialogueNodeDataLine>(NewNode));

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