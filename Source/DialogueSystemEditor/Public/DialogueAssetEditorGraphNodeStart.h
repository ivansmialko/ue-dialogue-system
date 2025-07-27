#pragma once

#include "EdGraph/EdGraph.h"
#include "DialogueAssetEditorGraphNodeBase.h"

#include "DialogueAssetEditorGraphNodeStart.generated.h"

UCLASS()
class UDialogueAssetEditorGraphNodeStart : public UDialogueAssetEditorGraphNodeBase
{
	GENERATED_BODY()

//public methods
public:
//Begin UEdGraphNode interface
	virtual FText GetNodeTitle(ENodeTitleType::Type InNodeTitleType) const override { return FText::FromString(TEXT("Start")); }
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(FColor::Red); }
	virtual bool CanUserDeleteNode() const override { return false; }
//End UEdGraphNode interface

//Begin UDialogueAssetEditorGraphNodeBase interface
	virtual UEdGraphPin* CreateDialoguePin(const EEdGraphPinDirection& InDirection, FName InName) override;
//End UDialogueAssetEditorGraphNodeBase interface
};