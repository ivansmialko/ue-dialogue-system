#pragma once

#include "CoreMinimal.h"
#include "DialogueAsset.generated.h"

class UDialogueGraph;

UCLASS(BlueprintType)
class DIALOGUESYSTEMRUNTIME_API UDialogueAsset : public UObject
{
	GENERATED_BODY()

//public fields
public:
	UPROPERTY(EditAnywhere)
	FString DialogueName = TEXT("Enter dialogue name here");

	UPROPERTY()
	UDialogueGraph* Graph{ nullptr };
};