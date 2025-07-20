#include "CustomAssetEditorApp.h"
#include "CustomAssetEditorAppTabMode.h"

void CustomAssetEditorApp::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	FWorkflowCentricApplication::RegisterTabSpawners(InTabManager);
}

void CustomAssetEditorApp::InitEditor(const EToolkitMode::Type InMode, const TSharedPtr<class IToolkitHost>& InToolkitHost, UObject* InCustomAsset)
{
	TArray<UObject*> ObjectsToEdit;
	ObjectsToEdit.Add(InCustomAsset);

	InitAssetEditor(
		InMode,
		InToolkitHost,
		TEXT("CustomAssetEditor"),
		FTabManager::FLayout::NullLayout,
		true,
		true,
		ObjectsToEdit
	);

	AddApplicationMode(TEXT("CustomAssetEditorAppTabMode"), MakeShareable(new CustomAssetEditorAppTabMode(SharedThis(this))));
	SetCurrentMode(TEXT("CustomAssetEditorAppTabMode"));
}
