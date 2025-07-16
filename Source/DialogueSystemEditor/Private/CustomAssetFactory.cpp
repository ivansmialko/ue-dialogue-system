#include "CustomAssetFactory.h"
#include "CustomAsset.h"

UCustomAssetFactory::UCustomAssetFactory(const FObjectInitializer& InObjectInitializer) : Super(InObjectInitializer)
{
	SupportedClass = UCustomAsset::StaticClass();
}

UObject* UCustomAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn)
{
	UCustomAsset* NewAsset = NewObject<UCustomAsset>(InParent, InName, InFlags);
	return NewAsset;
}

bool UCustomAssetFactory::CanCreateNew() const
{
	return true;
}
