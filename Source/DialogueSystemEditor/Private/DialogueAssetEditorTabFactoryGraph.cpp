#include "DialogueAssetEditorTabFactoryGraph.h"
#include "DialogueAssetEditorApp.h"
#include "DialogueAsset.h"
#include "IDetailsView.h"
#include "PropertyEditorModule.h"
#include "GraphEditor.h"
#include "Editor/UnrealEd/Public/Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"

DialogueAssetEditorTabFactoryGraph::DialogueAssetEditorTabFactoryGraph(TSharedPtr<DialogueAssetEditorApp> InApp):
	FWorkflowTabFactory(FName("DialogueAssetEditorTabFactoryGraph"), InApp)
{
	App = InApp;
	TabLabel = FText::FromString(TEXT("Graph editor"));
	ViewMenuDescription = FText::FromString(TEXT("Dialogue graph editor"));
	ViewMenuTooltip = FText::FromString(TEXT("Shows current dialogue graph editor"));
}

TSharedRef<SWidget> DialogueAssetEditorTabFactoryGraph::CreateTabBody(const FWorkflowTabSpawnInfo& InInfo) const
{
	const TSharedPtr<DialogueAssetEditorApp> Application = App.Pin();

	SGraphEditor::FGraphEditorEvents GraphEvents;
	GraphEvents.OnSelectionChanged.BindRaw(Application.Get(), &DialogueAssetEditorApp::OnGraphSelectionHandler);

	const TSharedPtr<SGraphEditor> GraphEditor = SNew(SGraphEditor)
		.IsEditable(true)
		.GraphEvents(GraphEvents)
		.GraphToEdit(Application->GetWorkingGraph());

	Application->SetWorkingGraphUi(GraphEditor);

	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		.HAlign(HAlign_Fill)
		[
			GraphEditor.ToSharedRef()
		];
}

FText DialogueAssetEditorTabFactoryGraph::GetTabToolTipText(const FWorkflowTabSpawnInfo& InInfo) const
{
	return FText::FromString(TEXT("Dialogue graph editor"));
}
