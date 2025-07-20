#include "CustomAssetAction.h"
#include "CustomAsset.h"
#include "CustomAssetEditorApp.h"

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
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (UObject* CurrObject : InObjects)
	{
		UCustomAsset* CustomAsset = Cast<UCustomAsset>(CurrObject);
		if(!CustomAsset)
			continue;

		TSharedRef<CustomAssetEditorApp> Editor(new CustomAssetEditorApp());
		Editor->InitEditor(Mode, EditWithinLevelEditor, CustomAsset);
	}
}

uint32 CustomAssetAction::GetCategories()
{
	return AssetCategory;
}
