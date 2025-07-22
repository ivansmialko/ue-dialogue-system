#include "DialogueAssetAction.h"
#include "DialogueAsset.h"
#include "DialogueAssetEditorApp.h"

DialogueAssetAction::DialogueAssetAction(EAssetTypeCategories::Type InCategory) : AssetCategory(InCategory){}

FText DialogueAssetAction::GetName() const
{
	return FText::FromString(TEXT("Dialogue"));
}

FColor DialogueAssetAction::GetTypeColor() const
{
	return FColor::Cyan;
}

UClass* DialogueAssetAction::GetSupportedClass() const
{
	return UDialogueAsset::StaticClass();
}

void DialogueAssetAction::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor /*= TSharedPtr<IToolkitHost>()*/)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (UObject* CurrObject : InObjects)
	{
		UDialogueAsset* CustomAsset = Cast<UDialogueAsset>(CurrObject);
		if(!CustomAsset)
			continue;

		TSharedRef<DialogueAssetEditorApp> Editor(new DialogueAssetEditorApp());
		Editor->InitEditor(Mode, EditWithinLevelEditor, CustomAsset);
	}
}

uint32 DialogueAssetAction::GetCategories()
{
	return AssetCategory;
}
