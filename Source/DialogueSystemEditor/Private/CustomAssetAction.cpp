#include "CustomAssetAction.h"
#include "CustomAsset.h"

CustomAssetAction::CustomAssetAction(EAssetTypeCategories::Type InCategory) : AssetCategory(InCategory){}

FText CustomAssetAction::GetName() const
{
	return FText::FromString(TEXT("MyCustomAsset"));
}

FColor CustomAssetAction::GetTypeColor() const
{
	return FColor::Cyan;
}

UClass* CustomAssetAction::GetSupportedClass() const
{
	return UCustomAsset::StaticClass();
}

void CustomAssetAction::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor /*= TSharedPtr<IToolkitHost>()*/)
{
	// TODO
}

uint32 CustomAssetAction::GetCategories()
{
	return AssetCategory;
}
