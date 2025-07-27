#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"
#include "SGraphPanel.h"

class UDialogueAsset;
class UEdGraph;
class IDetailsView;

class DialogueAssetEditorApp : public FWorkflowCentricApplication, public FEditorUndoClient, public FNotifyHook
{
//private fields
private:
	UDialogueAsset* WorkingAsset{ nullptr };
	UEdGraph* WorkingGraph{ nullptr };

	//Working graph ui part (slate widget)
	TSharedPtr<SGraphEditor> WorkingGraphUi{ nullptr };
	TSharedPtr<IDetailsView> SelectedNodeDetailsView{ nullptr };

	FDelegateHandle OnGraphChangeDlg;

//public methods
public:
	void InitEditor(const EToolkitMode::Type InMode, const TSharedPtr<class IToolkitHost>& InToolkitHost, UObject* InCustomAsset);
	void OnGraphChangeHandler(const FEdGraphEditAction& InEditAction) const;
	void OnGraphSelectionHandler(const FGraphPanelSelectionSet& InSelection) const;
	void OnNodeDetailsViewUpdated(const FPropertyChangedEvent& InEvent) const;

//Begin FWorkflowCentricApplication interface
	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;
	virtual void OnClose() override;
//End FWorkflowCentricApplication interface

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
	void UpdateWorkingGraph() const;

//getters/setters
public:
	void SetWorkingGraphUi(const TSharedPtr<SGraphEditor>& InWorkingGraphUi) { WorkingGraphUi = InWorkingGraphUi; }
	void SetSelectedNodeDetailView(const TSharedPtr<IDetailsView>& InDetailsView);

	UDialogueAsset* GetWorkingAsset() const { return WorkingAsset;  }
	UEdGraph* GetWorkingGraph() const { return WorkingGraph; }
};