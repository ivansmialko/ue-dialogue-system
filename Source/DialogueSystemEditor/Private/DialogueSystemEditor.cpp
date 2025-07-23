// Copyright Epic Games, Inc. All Rights Reserved.

#include "DialogueSystemEditor.h"
#include "DialogueAssetEditorGraphPin.h"
#include "EdGraphUtilities.h"
#include "IAssetTools.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FDialogueSystemEditorModule"

void FDialogueSystemEditorModule::StartupModule()
{
	IAssetTools& AssetToolsModule = IAssetTools::Get();
	const EAssetTypeCategories::Type AssetType = AssetToolsModule.RegisterAdvancedAssetCategory(FName(TEXT("DialogueSystem")), FText::FromString("Dialogue System"));
	const TSharedPtr<DialogueAssetAction> CustomAction = MakeShareable(new DialogueAssetAction(AssetType));
	AssetToolsModule.RegisterAssetTypeActions(CustomAction.ToSharedRef());

	const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin("DialogueSystem");
	const FString ContentDirectory = Plugin->GetContentDir();
	StyleSet = MakeShareable(new FSlateStyleSet(TEXT("DialogEditorStyle")));
	StyleSet->SetContentRoot(ContentDirectory);

	FSlateImageBrush* ThumbnailBrush = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("dialogue_thumbnail"), TEXT(".png")), FVector2D(128.0, 128.0));
	FSlateImageBrush* IconBrush = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("dialogue_icon"), TEXT(".png")), FVector2D(128.0, 128.0));
	FSlateImageBrush* NodePinAddIcon = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("node_pin_add"), TEXT(".png")), FVector2D(128.0, 128.0));
	FSlateImageBrush* NodePinDeleteIcon = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("node_pin_delete"), TEXT(".png")), FVector2D(128.0, 128.0));
	FSlateImageBrush* NodeDeleteIcon = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("node_delete"), TEXT(".png")), FVector2D(128.0, 128.0));
	StyleSet->Set(TEXT("ClassThumbnail.DialogueAsset"), ThumbnailBrush);
	StyleSet->Set(TEXT("ClassIcon.DialogueAsset"), IconBrush);
	StyleSet->Set(TEXT("DialogueAssetEditor.NodePinAddIcon"), NodePinAddIcon);
	StyleSet->Set(TEXT("DialogueAssetEditor.NodePinRemoveIcon"), NodePinDeleteIcon);
	StyleSet->Set(TEXT("DialogueAssetEditor.NodeDelete"), NodeDeleteIcon);

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);

	GraphNodePinFactory = MakeShareable(new FDialogueAssetEditorGraphPinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(GraphNodePinFactory);
}

void FDialogueSystemEditorModule::ShutdownModule()
{
	if (!StyleSet.IsValid())
		return;

	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
	FEdGraphUtilities::RegisterVisualPinFactory(GraphNodePinFactory);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDialogueSystemEditorModule, DialogueSystemEditor)