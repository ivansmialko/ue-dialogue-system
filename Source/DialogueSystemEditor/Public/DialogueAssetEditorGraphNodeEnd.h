#pragma once

#include "DialogueAssetEditorGraphNodeBase.h"
#include "DialogueNodeType.h"
#include "DialogueNodeDataEnd.h"

#include "DialogueAssetEditorGraphNodeEnd.generated.h"

UCLASS()
class UDialogueAssetEditorGraphNodeEnd : public UDialogueAssetEditorGraphNodeBase
{
	GENERATED_BODY()

//protected fields
protected:
	UPROPERTY()
	UDialogueNodeDataEnd* NodeData { nullptr };

//public methods
public:
//Begin UEdGraphNode interface
	virtual FText GetNodeTitle(ENodeTitleType::Type InNodeTitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(FColor::Purple); }
	virtual bool CanUserDeleteNode() const override { return true; }
	virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;
//End UEdGraphNode interface

//Begin UDialogueAssetEditorGraphNodeBase interface
	virtual UEdGraphPin* CreateDialoguePin(const EEdGraphPinDirection& InDirection, FName InName) override;
	virtual UEdGraphPin* CreateDefaultInputPin() override;
	virtual EDialogueNodeType GetDialogueNodeType() const override { return EDialogueNodeType::EDNT_End; }
	virtual void CreateDefaultOutputPins() override;
	virtual void InitNodeData(UObject* Output) override { NodeData = NewObject<UDialogueNodeDataEnd>(Output); }
	virtual void OnPropertiesChanged() override { Modify(); };
	virtual void SetNodeData(UDialogueNodeDataBase* InNodeData) override { NodeData = Cast<UDialogueNodeDataEnd>(InNodeData); }
	virtual UDialogueNodeDataBase* GetNodeData() const override { return Cast<UDialogueNodeDataBase>(NodeData); }
//End UDialogueAssetEditorGraphNodeBase interface
};