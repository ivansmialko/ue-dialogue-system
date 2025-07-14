#pragma once

#include "CoreMinimal.h"
#include "CustomAssetFactory.generated.h"

UCLASS()
class UCustomAssetFactory : public UFactory
{
	GENERATED_BODY()

public:
	UCustomAssetFactory(const FObjectInitializer& InObjectInitializer);

//Begin UFactory interface
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn);
	virtual bool CanCreateNew() const override;
//End UFactory interface
};