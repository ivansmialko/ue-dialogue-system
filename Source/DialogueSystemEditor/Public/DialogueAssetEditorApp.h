#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"

class UDialogueAsset;
class UEdGraph;

class DialogueAssetEditorApp : public FWorkflowCentricApplication, public FEditorUndoClient, public FNotifyHook
{
//private fields
private:
	UDialogueAsset* WorkingAsset{ nullptr };
	UEdGraph* WorkingGraph{ nullptr };

//public methods
public:
	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;
	void InitEditor(const EToolkitMode::Type InMode, const TSharedPtr<class IToolkitHost>& InToolkitHost, UObject* InCustomAsset);


//Begin FAssetEditorToolkit interface
	virtual FName GetToolkitFName() const override { return FName(TEXT("DialogueAssetEditorApp")); }
	virtual FText GetBaseToolkitName() const override { return FText::FromString(TEXT("DialogueAssetEditorApp")); }
	virtual FString GetWorldCentricTabPrefix() const override { return TEXT("DialogueAssetEditorApp"); }
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f); }
	virtual FString GetDocumentationLink() const override { return TEXT("https://github.com/ivansmialko/ue-dialogue-system"); }
	virtual void OnToolkitHostingStarted(const TSharedRef<class IToolkit>& InToolkit) override {}
	virtual void OnToolkitHostingFinished(const TSharedRef<class IToolkit>& InToolkit) override {}
//End FAssetEditorToolkit interface

protected:
	void UpdateWorkingAsset() const;
	void UpdateWorkingGraph();

//getters/setters
public:
	UDialogueAsset* GetWorkingAsset() const { return WorkingAsset;  }
	UEdGraph* GetWorkingGraph() const { return WorkingGraph; }
};