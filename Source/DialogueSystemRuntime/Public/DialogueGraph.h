#pragma once

#include "CoreMinimal.h"
#include "UObject/NameTypes.h"

#include "DialogueGraph.generated.h"

class UDialogueNodeDataBase;

UENUM()
enum class EDialogueNode : uint8
{
	EDN_Unknown,
	EDN_Start,
	EDN_Dialogue,
	EDN_End
};

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
	UDialogueNodeDataBase* Data;

	UPROPERTY()
	EDialogueNode Type{ EDialogueNode::EDN_Dialogue };
};

UCLASS()
class DIALOGUESYSTEMRUNTIME_API UDialogueGraph : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<UDialogueGraphNode*> Nodes;
};