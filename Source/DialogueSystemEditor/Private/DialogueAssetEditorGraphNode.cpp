#include "DialogueAssetEditorGraphNode.h"

#include "Framework/Commands/UIAction.h"
#include "ToolMenu.h"

UDialogueAssetEditorGraphNode::UDialogueAssetEditorGraphNode()
{
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
				ThisNode->CreateCustomPin(EGPD_Output, TEXT("Output"));
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

UEdGraphPin* UDialogueAssetEditorGraphNode::CreateCustomPin(const EEdGraphPinDirection& InDirection, FName InName)
{
	const FName Category = (InDirection == EGPD_Input ? TEXT("Inputs") : TEXT("Outputs"));
	const FName Subcategory = TEXT("Custom pin");

	UEdGraphPin* Pin = CreatePin(InDirection, Category, InName);
	Pin->PinType.PinSubCategory = Subcategory;

	return Pin;
}
