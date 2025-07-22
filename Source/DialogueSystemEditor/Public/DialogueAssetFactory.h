#pragma once

#include "CoreMinimal.h"
#include "DialogueAssetFactory.generated.h"

UCLASS()
class UDialogueAssetFactory : public UFactory
{
	GENERATED_BODY()

public:
	UDialogueAssetFactory(const FObjectInitializer& InObjectInitializer);

//Begin UFactory interface
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn) override;
	virtual bool CanCreateNew() const override;
//End UFactory interface
};