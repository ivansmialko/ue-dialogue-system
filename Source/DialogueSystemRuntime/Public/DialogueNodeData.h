#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeData.generated.h"

UCLASS(BlueprintType)
class DIALOGUESYSTEMRUNTIME_API UDialogueNodeData : public UObject
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