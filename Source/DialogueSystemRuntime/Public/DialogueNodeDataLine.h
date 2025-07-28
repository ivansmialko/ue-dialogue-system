#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeDataBase.h"
#include "DialogueNodeDataLine.generated.h"

UCLASS(BlueprintType)
class DIALOGUESYSTEMRUNTIME_API UDialogueNodeDataLine : public UDialogueNodeDataBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FText Title;

	UPROPERTY(EditAnywhere)
	FText Text;

	UPROPERTY(EditAnywhere)
	TArray<FText> Responses;
};