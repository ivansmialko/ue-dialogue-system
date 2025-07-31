#include "DialogueAssetEditorGraphNodeEnd.h"

FText UDialogueAssetEditorGraphNodeEnd::GetNodeTitle(ENodeTitleType::Type InNodeTitleType) const
{
	if (!NodeData)
		return FText::FromString(TEXT("End"));

	if (NodeData->Action == EDialogueNodeDataEndAction::None)
		return FText::FromString(TEXT("End"));

	const FString ActionType = UEnum::GetDisplayValueAsText(NodeData->Action).ToString();
	if (ActionType.IsEmpty())
		return FText::FromString(ActionType);

	FString ActionData = NodeData->ActionData;
	if (ActionData.Len() > 15)
	{
		ActionData = ActionData.Left(15) + TEXT("...");
	}

	return FText::FromString(ActionType + TEXT(" - ") + ActionData);
}

void UDialogueAssetEditorGraphNodeEnd::GetNodeContextMenuActions(UToolMenu* Menu,
	UGraphNodeContextMenuContext* Context) const
{
	UDialogueAssetEditorGraphNodeEnd* ThisNode = const_cast<UDialogueAssetEditorGraphNodeEnd*>(this);

	FToolMenuSection& MenuSection = Menu->AddSection(TEXT("DefaultSection"), FText::FromString(TEXT("End node actions")));
	MenuSection.AddMenuEntry
	(
		TEXT("NodeDelete"),
		FText::FromString(TEXT("Delete node")),
		FText::FromString(TEXT("Deletes a node")),
		FSlateIcon(TEXT("DialogEditorStyle"), TEXT("DialogueAssetEditor.NodeDelete")),
		FUIAction(FExecuteAction::CreateLambda([ThisNode]()
			{
				ThisNode->GetGraph()->RemoveNode(ThisNode);
			}))
	);
}

UEdGraphPin* UDialogueAssetEditorGraphNodeEnd::CreateDialoguePin(const EEdGraphPinDirection& InDirection, FName InName)
{
	const FName Category = TEXT("Inputs");
	const FName Subcategory = TEXT("NodeEndInput");

	UEdGraphPin* Pin = CreatePin(InDirection, Category, InName);
	Pin->PinType.PinSubCategory = Subcategory;

	return Pin;
}

UEdGraphPin* UDialogueAssetEditorGraphNodeEnd::CreateDefaultInputPin()
{
	return CreateDialoguePin(EEdGraphPinDirection::EGPD_Input, FName(TEXT("End")));
}

void UDialogueAssetEditorGraphNodeEnd::CreateDefaultOutputPins()
{
	//No output pins available in the end node
}
