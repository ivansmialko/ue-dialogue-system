#pragma once

#include "EdGraph/EdGraphNode.h"
#include "DialogueAssetEditorGraphNodeBase.generated.h"

class UDialogueNodeData;

UCLASS()
class UDialogueAssetEditorGraphNodeBase : public UEdGraphNode
{
	GENERATED_BODY()

//protected fields
protected:
	UPROPERTY()
	UDialogueNodeData* NodeData{ nullptr };

//public methods
public:
	virtual UEdGraphPin* CreateDialoguePin(const EEdGraphPinDirection& InDirection, FName InName);

//getters/setters
public:
	FORCEINLINE void SetNodeData(UDialogueNodeData* InNodeData) { NodeData = InNodeData; }
	FORCEINLINE UDialogueNodeData* GetNodeData() const { return NodeData; }
};