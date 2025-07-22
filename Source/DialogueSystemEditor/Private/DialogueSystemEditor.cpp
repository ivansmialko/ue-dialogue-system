// Copyright Epic Games, Inc. All Rights Reserved.

#include "DialogueSystemEditor.h"
#include "DialogueAsset.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FDialogueSystemEditorModule"

void FDialogueSystemEditorModule::StartupModule()
{
	IAssetTools& AssetToolsModule = IAssetTools::Get();
	const EAssetTypeCategories::Type AssetType = AssetToolsModule.RegisterAdvancedAssetCategory(FName(TEXT("DialogueSystem")), FText::FromString("Dialogue system"));
	const TSharedPtr<DialogueAssetAction> CustomAction = MakeShareable(new DialogueAssetAction(AssetType));
	AssetToolsModule.RegisterAssetTypeActions(CustomAction.ToSharedRef());

	const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin("DialogueSystem");
	const FString ContentDirectory = Plugin->GetContentDir();
	StyleSet = MakeShareable(new FSlateStyleSet(TEXT("CustomAssetEditorStyle")));
	StyleSet->SetContentRoot(ContentDirectory);

	FSlateImageBrush* ThumbnailBrush = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("dialogue_thumbnail"), TEXT(".png")), FVector2D(128.0, 128.0));
	FSlateImageBrush* IconBrush = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("dialogue_icon"), TEXT(".png")), FVector2D(128.0, 128.0));
	StyleSet->Set(TEXT("ClassThumbnail.CustomAsset"), ThumbnailBrush);
	StyleSet->Set(TEXT("ClassIcon.CustomAsset"), IconBrush);

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
}

void FDialogueSystemEditorModule::ShutdownModule()
{
	if (!StyleSet.IsValid())
		return;

	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDialogueSystemEditorModule, DialogueSystemEditor)