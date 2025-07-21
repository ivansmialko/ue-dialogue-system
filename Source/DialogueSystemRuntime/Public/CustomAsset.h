#pragma once

#include "CoreMinimal.h"
#include "CustomAsset.generated.h"

UCLASS(BlueprintType)
class DIALOGUESYSTEMRUNTIME_API UCustomAsset : public UObject
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
};