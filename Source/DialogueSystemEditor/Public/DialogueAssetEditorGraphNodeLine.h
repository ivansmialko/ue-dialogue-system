#pragma once

#include "EdGraph/EdGraphNode.h"
#include "DialogueAssetEditorGraphNodeBase.h"
#include "DialogueNodeDataBase.h"
#include "DialogueNodeDataLine.h"

#include "DialogueAssetEditorGraphNodeLine.generated.h"

class UToolMenu;
class UGraphNodeContextMenuContext;

UCLASS()
class UDialogueAssetEditorGraphNodeLine : public UDialogueAssetEditorGraphNodeBase
{
	GENERATED_BODY()

//protected members
protected:
	UPROPERTY()
	UDialogueNodeDataLine* NodeData{ nullptr };

//public methods
public:
	UDialogueAssetEditorGraphNodeLine();
	void SyncPinsWithResponses();

	UDialogueNodeDataLine* GetNodeDataLine() const { return Cast<UDialogueNodeDataLine>(NodeData); }

//Begin UDialogueAssetEditorGraphNodeBase interface
	virtual UEdGraphPin* CreateDialoguePin(const EEdGraphPinDirection& InDirection, FName InName) override;
	virtual UEdGraphPin* CreateDefaultInputPin() override;
	virtual EDialogueNodeType GetDialogueNodeType() const override { return EDialogueNodeType::EDNT_Line; }
	virtual void CreateDefaultOutputPins() override;
	virtual void InitNodeData(UObject* Output) override { NodeData = NewObject<UDialogueNodeDataLine>(Output); }
	virtual void OnPropertiesChanged() override { SyncPinsWithResponses(); }
	virtual void SetNodeData(UDialogueNodeDataBase* InNodeData) override { NodeData = Cast<UDialogueNodeDataLine>(InNodeData); }
	virtual UDialogueNodeDataBase* GetNodeData() const override { return NodeData; }

//End UDialogueAssetEditorGraphNodeBase interface

//Begin UEdGraphNode interface
	virtual FText GetNodeTitle(ENodeTitleType::Type InNodeTitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(FColor::Green); }
	virtual bool CanUserDeleteNode() const override { return true; }
	virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;
//End UEdGraphNode interface
};