#pragma once

#include "EdGraph/EdGraphNode.h"
#include "DialogueAssetEditorGraphNode.generated.h"

class UToolMenu;
class UGraphNodeContextMenuContext;
class UDialogueNodeData;

UCLASS()
class UDialogueAssetEditorGraphNode : public UEdGraphNode
{
	GENERATED_BODY()

//private fields
private:
	UPROPERTY()
	UDialogueNodeData* NodeData{ nullptr };

//public methods
public:
	UDialogueAssetEditorGraphNode();
	UEdGraphPin* CreateCustomPin(const EEdGraphPinDirection& InDirection, FName InName);

//Begin UEdGraphNode interface
	virtual FText GetNodeTitle(ENodeTitleType::Type InNodeTitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(FColor::Green); }
	virtual bool CanUserDeleteNode() const override { return true; }
	virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;
//End UEdGraphNode interface

//getters/setters
public:
	FORCEINLINE void SetNodeData(UDialogueNodeData* InNodeData) { NodeData = InNodeData; }

	FORCEINLINE UDialogueNodeData* GetNodeData() const { return NodeData; }
};