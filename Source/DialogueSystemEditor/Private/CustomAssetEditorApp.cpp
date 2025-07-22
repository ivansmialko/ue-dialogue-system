#include "CustomAssetEditorApp.h"
#include "CustomAsset.h"
#include "CustomAssetEditorAppTabMode.h"
#include "CustomAssetEditorAppGraphSchema.h"

#include "Kismet2/BlueprintEditorUtils.h"

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

	WorkingAsset = Cast<UCustomAsset>(InCustomAsset);
	WorkingGraph = FBlueprintEditorUtils::CreateNewGraph(WorkingAsset, NAME_None, UEdGraph::StaticClass(), UCustomGraphSchema::StaticClass());

	AddApplicationMode(TEXT("CustomAssetEditorAppTabMode"), MakeShareable(new CustomAssetEditorAppTabMode(SharedThis(this))));
	SetCurrentMode(TEXT("CustomAssetEditorAppTabMode"));
}
