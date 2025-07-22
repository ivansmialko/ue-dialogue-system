#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"

#include "CustomAssetEditorAppGraphSchema.generated.h"

UCLASS()
class UCustomGraphSchema : public UEdGraphSchema
{
	GENERATED_BODY()

//public methods
public:
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& InContextMenuBuilder) const override;
};

USTRUCT()
struct FNewNodeAction : public FEdGraphSchemaAction
{
	GENERATED_BODY()

//public methods
public:
	FNewNodeAction();
	FNewNodeAction(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, const int32 InGrouping);

	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;
};
