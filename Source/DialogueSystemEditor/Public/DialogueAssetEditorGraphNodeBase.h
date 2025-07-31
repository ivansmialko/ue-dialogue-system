#pragma once

#include "EdGraph/EdGraphNode.h"
#include "DialogueNodeType.h"

#include "DialogueAssetEditorGraphNodeBase.generated.h"

class UDialogueNodeDataBase;

UCLASS()
class UDialogueAssetEditorGraphNodeBase : public UEdGraphNode
{
	GENERATED_BODY()

//public methods
public:
	virtual UEdGraphPin* CreateDialoguePin(const EEdGraphPinDirection& InDirection, FName InName) { return nullptr; }
	virtual UEdGraphPin* CreateDefaultInputPin() { return nullptr; }
	virtual EDialogueNodeType GetDialogueNodeType() const { return EDialogueNodeType::EDNT_Unknown; }
	virtual void CreateDefaultOutputPins() { /* Don't do anything by default */}
	virtual void InitNodeData(UObject* Parent) { /* Nothing by default */ }
	virtual void OnPropertiesChanged() { /* Nothing by default */}

//getters/setters
public:
	virtual void SetNodeData(UDialogueNodeDataBase* InNodeData) { /* Nothing by default */ }
	virtual UDialogueNodeDataBase* GetNodeData() const { return nullptr; }
};