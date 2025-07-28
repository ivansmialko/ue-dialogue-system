#pragma once

#include "EdGraph/EdGraphNode.h"
#include "DialogueAssetEditorGraphNodeBase.h"

#include "DialogueAssetEditorGraphNodeLine.generated.h"

class UToolMenu;
class UGraphNodeContextMenuContext;

UCLASS()
class UDialogueAssetEditorGraphNodeLine : public UDialogueAssetEditorGraphNodeBase
{
	GENERATED_BODY()

//public methods
public:
	UDialogueAssetEditorGraphNodeLine();
	void SyncPinsWithResponses();

//Begin UDialogueAssetEditorGraphNodeBase interface
	virtual UEdGraphPin* CreateDialoguePin(const EEdGraphPinDirection& InDirection, FName InName) override;
//End UDialogueAssetEditorGraphNodeBase interface

//Begin UEdGraphNode interface
	virtual FText GetNodeTitle(ENodeTitleType::Type InNodeTitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(FColor::Green); }
	virtual bool CanUserDeleteNode() const override { return true; }
	virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;
//End UEdGraphNode interface
};