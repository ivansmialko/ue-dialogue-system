#include "DialogueAssetFactory.h"
#include "DialogueAsset.h"

UDialogueAssetFactory::UDialogueAssetFactory(const FObjectInitializer& InObjectInitializer) : Super(InObjectInitializer)
{
	SupportedClass = UDialogueAsset::StaticClass();
}

UObject* UDialogueAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn)
{
	UDialogueAsset* NewAsset = NewObject<UDialogueAsset>(InParent, InName, InFlags);
	return NewAsset;
}

bool UDialogueAssetFactory::CanCreateNew() const
{
	return true;
}
