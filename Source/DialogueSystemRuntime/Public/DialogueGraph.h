#pragma once

#include "CoreMinimal.h"
#include "UObject/NameTypes.h"

#include "DialogueNodeData.h"

#include "DialogueGraph.generated.h"

class UDialogueNodeData;

UCLASS()
class DIALOGUESYSTEMRUNTIME_API UDialogueGraphPin : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FName Name;

	UPROPERTY()
	FGuid Id;

	UPROPERTY()
	UDialogueGraphPin* Connection{ nullptr };
};

UCLASS()
class DIALOGUESYSTEMRUNTIME_API UDialogueGraphNode : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UDialogueGraphPin* Input{ nullptr };

	UPROPERTY()
	TArray<UDialogueGraphPin*> Outputs;

	UPROPERTY()
	FVector2D Position;

	UPROPERTY()
	UDialogueNodeData* Data;
};

UCLASS()
class DIALOGUESYSTEMRUNTIME_API UDialogueGraph : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<UDialogueGraphNode*> Nodes;
};