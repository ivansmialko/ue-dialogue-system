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
	FString AssetName;

	UPROPERTY(EditAnywhere)
	int32 AssetInteger;

	UPROPERTY(EditAnywhere)
	bool AssetBool;

	UPROPERTY()
	UDialogueGraph* Graph{ nullptr };
};