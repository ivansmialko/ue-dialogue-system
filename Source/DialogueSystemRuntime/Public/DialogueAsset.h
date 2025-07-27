#pragma once

#include <functional>

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

//private fields
private:
	std::function<void()> PreSaveListener{ nullptr };

//public methods
public:
	void SetPreSaveListener(const std::function<void()>& InPreSaveListener) { PreSaveListener = InPreSaveListener; }

//UObject interface begin
	virtual void PreSave(FObjectPreSaveContext SaveContext) override;
//UObject interface end
};