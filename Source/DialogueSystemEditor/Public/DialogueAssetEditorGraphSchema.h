#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"

#include "DialogueAssetEditorGraphSchema.generated.h"

UCLASS()
class UDialogueAssetEditorGraphSchema : public UEdGraphSchema
{
	GENERATED_BODY()

//public methods
public:
//Begin UEdGraphSchema interface
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& InContextMenuBuilder) const override;
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* InA, const UEdGraphPin* InB) const override;
	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;
//End UEdGraphSchema interface
};

USTRUCT()
struct FNewNodeAction : public FEdGraphSchemaAction
{
	GENERATED_BODY()


//protected members
protected:
	UClass* ClassTemplate{ nullptr };

//public methods
public:
//Begin UEdGraphSchemaAction interface
	FNewNodeAction();
	FNewNodeAction(UClass* InClassTemplate, const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, const int32 InGrouping);

	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;
//End UEdGraphSchemaAction interface
};
