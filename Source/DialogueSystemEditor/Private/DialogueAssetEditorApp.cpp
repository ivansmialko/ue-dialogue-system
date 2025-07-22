#include "DialogueAssetEditorApp.h"
#include "DialogueAsset.h"
#include "DialogueAssetEditorTabModeMain.h"
#include "DialogueAssetEditorGraphSchema.h"

#include "Kismet2/BlueprintEditorUtils.h"

void DialogueAssetEditorApp::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	FWorkflowCentricApplication::RegisterTabSpawners(InTabManager);
}

void DialogueAssetEditorApp::InitEditor(const EToolkitMode::Type InMode, const TSharedPtr<class IToolkitHost>& InToolkitHost, UObject* InCustomAsset)
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

	WorkingAsset = Cast<UDialogueAsset>(InCustomAsset);
	WorkingGraph = FBlueprintEditorUtils::CreateNewGraph(WorkingAsset, NAME_None, UEdGraph::StaticClass(), UDialogueAssetEditorGraphSchema::StaticClass());

	AddApplicationMode(TEXT("DialogueAssetEditorTabModeMain"), MakeShareable(new DialogueAssetEditorTabModeMain(SharedThis(this))));
	SetCurrentMode(TEXT("DialogueAssetEditorTabModeMain"));
}
