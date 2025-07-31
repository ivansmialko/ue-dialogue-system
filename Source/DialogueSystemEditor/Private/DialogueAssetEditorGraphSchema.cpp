#include "DialogueAssetEditorGraphSchema.h"
#include "DialogueAssetEditorGraphNodeLine.h"
#include "DialogueAssetEditorGraphNodeStart.h"
#include "DialogueAssetEditorGraphNodeEnd.h"
#include "DialogueNodeDataLine.h"

void UDialogueAssetEditorGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& InContextMenuBuilder) const
{
	const TSharedPtr<FNewNodeAction> ActionCreateNodeLine
	(
		new FNewNodeAction
		(
			UDialogueAssetEditorGraphNodeLine::StaticClass(),
			FText::FromString(TEXT("Nodes")),
			FText::FromString(TEXT("New dialogue line")),
			FText::FromString(TEXT("Creates a new dialogue line")),
			0
		)
	);

	const TSharedPtr<FNewNodeAction> ActionCreateNodeEnd
	(
		new FNewNodeAction
		(
			UDialogueAssetEditorGraphNodeEnd::StaticClass(),
			FText::FromString(TEXT("Nodes")),
			FText::FromString(TEXT("New dialogue end")),
			FText::FromString(TEXT("Creates a new dialogue end")),
			0
		)
	);

	InContextMenuBuilder.AddAction(ActionCreateNodeLine);
	InContextMenuBuilder.AddAction(ActionCreateNodeEnd);
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

FNewNodeAction::FNewNodeAction(UClass* InClassTemplate, const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, const int32 InGrouping):
	FEdGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping), ClassTemplate(InClassTemplate)
{
}

UEdGraphNode* FNewNodeAction::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin,
	const FVector2f& Location, bool bSelectNewNode)
{
	UDialogueAssetEditorGraphNodeBase* NewNode = NewObject<UDialogueAssetEditorGraphNodeBase>(ParentGraph, ClassTemplate);
	NewNode->NodePosX = Location.X;
	NewNode->NodePosY = Location.Y;
	NewNode->CreateNewGuid();
	NewNode->InitNodeData(NewNode);
	
	if (UEdGraphPin* InputPin = NewNode->CreateDefaultInputPin())
	{
		NewNode->GetSchema()->TryCreateConnection(InputPin, FromPin);
	}

	ParentGraph->Modify();
	ParentGraph->AddNode(NewNode, true, true);

	return NewNode;
}