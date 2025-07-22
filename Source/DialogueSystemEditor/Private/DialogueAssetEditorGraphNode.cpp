#include "DialogueAssetEditorGraphNode.h"

#include "Framework/Commands/UIAction.h"
#include "ToolMenu.h"

void UDialogueAssetEditorGraphNode::GetNodeContextMenuActions(UToolMenu* Menu,
	UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& MenuSection = Menu->AddSection(TEXT("DefaultSection"), FText::FromString(TEXT("Default node actions")));
	MenuSection.AddMenuEntry
	(
		TEXT("AddPinEntry"),
		FText::FromString(TEXT("Add pin")),
		FText::FromString(TEXT("Creates a new pin")),

		)
}
