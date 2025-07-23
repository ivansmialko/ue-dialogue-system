#include "DialogueAssetEditorGraphNode.h"

#include "Framework/Commands/UIAction.h"
#include "ToolMenu.h"

UDialogueAssetEditorGraphNode::UDialogueAssetEditorGraphNode()
{
	CreatePin(EGPD_Input, TEXT("Inputs"), TEXT("Input"));
	CreatePin(EGPD_Output, TEXT("Outputs"), TEXT("Default output"));
}

void UDialogueAssetEditorGraphNode::GetNodeContextMenuActions(UToolMenu* Menu,
                                                              UGraphNodeContextMenuContext* Context) const
{
	UDialogueAssetEditorGraphNode* ThisNode = const_cast<UDialogueAssetEditorGraphNode*>(this);

	FToolMenuSection& MenuSection = Menu->AddSection(TEXT("DefaultSection"), FText::FromString(TEXT("Default node actions")));
	MenuSection.AddMenuEntry
	(
		TEXT("NodePinAdd"),
		FText::FromString(TEXT("Add pin")),
		FText::FromString(TEXT("Creates a new pin")),
		FSlateIcon(TEXT("DialogEditorStyle"), TEXT("DialogueAssetEditor.NodePinAddIcon")),
		FUIAction(FExecuteAction::CreateLambda([ThisNode]()
			{
				ThisNode->CreatePin(EGPD_Output, TEXT("Outputs"), TEXT("Another output"));
				ThisNode->GetGraph()->NotifyGraphChanged();
				ThisNode->GetGraph()->Modify();
			}))
	);

	MenuSection.AddMenuEntry
	(
		TEXT("NodePinRemove"),
		FText::FromString(TEXT("Remove pin")),
		FText::FromString(TEXT("Removes a last pin from the node")),
		FSlateIcon(TEXT("DialogEditorStyle"), TEXT("DialogueAssetEditor.NodePinRemoveIcon")),
		FUIAction(FExecuteAction::CreateLambda([ThisNode]()
			{
				if (ThisNode->Pins.Num() > 0)
				{
					UEdGraphPin* LastPin = ThisNode->GetPinAt(ThisNode->Pins.Num() - 1);
					if (LastPin && LastPin->Direction != EGPD_Input)
					{
						ThisNode->RemovePin(LastPin);
						ThisNode->GetGraph()->NotifyGraphChanged();
						ThisNode->GetGraph()->Modify();
					}
				}
			}))
	);

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
