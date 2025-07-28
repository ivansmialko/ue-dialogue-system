#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeDataBase.h"
#include "DialogueNodeDataEnd.generated.h"

UENUM(BlueprintType)
enum class EDialogueNodeDataEndAction : uint8
{
	None,
	StartQuest, //ActionData is the QuestId
};

UCLASS(BlueprintType)
class DIALOGUESYSTEMRUNTIME_API UDialogueNodeDataEnd : public UDialogueNodeDataBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	EDialogueNodeDataEndAction Action{ EDialogueNodeDataEndAction::None };

	UPROPERTY(EditAnywhere)
	FString ActionData{ TEXT("") };
};