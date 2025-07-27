#include "DialogueAssetEditorGraphNode.h"

#include "Framework/Commands/UIAction.h"
#include "ToolMenu.h"

#include "DialogueNodeData.h"

UDialogueAssetEditorGraphNode::UDialogueAssetEditorGraphNode()
{
}

FText UDialogueAssetEditorGraphNode::GetNodeTitle(ENodeTitleType::Type InNodeTitleType) const
{
	if (!NodeData)
		return FText::FromString("Dialogue node");

	if (NodeData->Title.IsEmpty() && NodeData->Text.IsEmpty())
		return FText::FromString("Dialogue node");

	if (NodeData->Title.IsEmpty() && !NodeData->Text.IsEmpty())
	{
		FString NodeTitle = NodeData->Text.ToString();
		if (NodeTitle.Len() > 15)
		{
			NodeTitle = NodeTitle.Left(15) + TEXT("...");
		}

		return FText::FromString(NodeTitle);
	}

	return NodeData->Title;
}

void UDialogueAssetEditorGraphNode::GetNodeContextMenuActions(UToolMenu* Menu,
                                                              UGraphNodeContextMenuContext* Context) const
{
	UDialogueAssetEditorGraphNode* ThisNode = const_cast<UDialogueAssetEditorGraphNode*>(this);

	FToolMenuSection& MenuSection = Menu->AddSection(TEXT("DefaultSection"), FText::FromString(TEXT("Default node actions")));
	MenuSection.AddMenuEntry
	(
		TEXT("NodePinAdd"),
		FText::FromString(TEXT("Add Response")),
		FText::FromString(TEXT("Creates a new response")),
		FSlateIcon(TEXT("DialogEditorStyle"), TEXT("DialogueAssetEditor.NodePinAddIcon")),
		FUIAction(FExecuteAction::CreateLambda([ThisNode]()
			{
				ThisNode->GetNodeData()->Responses.Add(FText::FromString(TEXT("Response")));
				ThisNode->SyncPinsWithResponses();

				ThisNode->GetGraph()->NotifyGraphChanged();
				ThisNode->GetGraph()->Modify();
			}))
	);

	MenuSection.AddMenuEntry
	(
		TEXT("NodePinRemove"),
		FText::FromString(TEXT("Remove Response")),
		FText::FromString(TEXT("Removes a last response from the node")),
		FSlateIcon(TEXT("DialogEditorStyle"), TEXT("DialogueAssetEditor.NodePinRemoveIcon")),
		FUIAction(FExecuteAction::CreateLambda([ThisNode]()
			{
				if (ThisNode->Pins.Num() > 0)
				{
					UEdGraphPin* LastPin = ThisNode->GetPinAt(ThisNode->Pins.Num() - 1);
					if (LastPin && LastPin->Direction != EGPD_Input)
					{
						UDialogueNodeData* NodeData = ThisNode->GetNodeData();
						NodeData->Responses.RemoveAt(NodeData->Responses.Num() - 1);

						ThisNode->SyncPinsWithResponses();
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

UEdGraphPin* UDialogueAssetEditorGraphNode::CreateDialoguePin(const EEdGraphPinDirection& InDirection, const FName InName)
{
	const FName Category = (InDirection == EGPD_Input ? TEXT("Inputs") : TEXT("Outputs"));
	const FName Subcategory = TEXT("DialogueSystemInputPin");

	UEdGraphPin* Pin = CreatePin(InDirection, Category, InName);
	Pin->PinType.PinSubCategory = Subcategory;

	return Pin;
}

void UDialogueAssetEditorGraphNode::SyncPinsWithResponses()
{
	//Sync the pins with the dialogue responses array
	//We're going to assume the first pin is always the input pin

	int NumPins = Pins.Num() - 1;
	int NumDataPins = NodeData->Responses.Num();

	while (NumPins > NumDataPins)
	{
		RemovePinAt(NumPins - 1, EGPD_Output);
		--NumPins;
	}

	while (NumDataPins > NumPins)
	{
		CreateDialoguePin(EEdGraphPinDirection::EGPD_Output, FName(NodeData->Responses[NumPins].ToString()));
		++NumPins;
	}

	int Index = 1;
	for (const FText& Response : NodeData->Responses)
	{
		GetPinAt(Index)->PinName = FName(Response.ToString());
		++Index;
	}
}
