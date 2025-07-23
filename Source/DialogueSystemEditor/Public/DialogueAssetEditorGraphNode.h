#pragma once

#include "EdGraph/EdGraphNode.h"
#include "DialogueAssetEditorGraphNode.generated.h"

class UToolMenu;
class UGraphNodeContextMenuContext;

UCLASS()
class UDialogueAssetEditorGraphNode : public UEdGraphNode
{
	GENERATED_BODY()

//public methods
public:
	UDialogueAssetEditorGraphNode();

	virtual FText GetNodeTitle(ENodeTitleType::Type InNodeTitleType) const override { return FText::FromString("Dialogue node"); }
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(FColor::Green); }
	virtual bool CanUserDeleteNode() const override { return true; }
	virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;
};