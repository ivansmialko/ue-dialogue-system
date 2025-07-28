#pragma once

#include "EdGraph/EdGraphNode.h"
#include "DialogueAssetEditorGraphNodeBase.generated.h"

class UDialogueNodeDataBase;

UCLASS()
class UDialogueAssetEditorGraphNodeBase : public UEdGraphNode
{
	GENERATED_BODY()

//protected fields
protected:
	UPROPERTY()
	UDialogueNodeDataBase* NodeData{ nullptr };

//public methods
public:
	virtual UEdGraphPin* CreateDialoguePin(const EEdGraphPinDirection& InDirection, FName InName) { return nullptr; }
	virtual UEdGraphPin* CreateDefaultPin() { return nullptr; }
	virtual void CreateDefaultOutputPins() { /* Don't do anything by default */}
	virtual void InitNodeInfo(UObject* Output) { /*Nothing by default */ }

//getters/setters
public:
	FORCEINLINE void SetNodeData(UDialogueNodeDataBase* InNodeData) { NodeData = InNodeData; }
	FORCEINLINE UDialogueNodeDataBase* GetNodeData() const { return NodeData; }
};