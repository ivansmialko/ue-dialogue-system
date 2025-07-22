#include "CustomAssetEditorAppTabFactoryGraph.h"
#include "CustomAssetEditorApp.h"
#include "CustomAsset.h"
#include "IDetailsView.h"
#include "PropertyEditorModule.h"
#include "GraphEditor.h"
#include "Editor/UnrealEd/Public/Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"

CustomAssetEditorAppTabFactoryGraph::CustomAssetEditorAppTabFactoryGraph(TSharedPtr<CustomAssetEditorApp> InApp):
	FWorkflowTabFactory(FName("CustomAssetEditorAppTabFactoryGraph"), InApp)
{
	App = InApp;
	TabLabel = FText::FromString(TEXT("Graph editor"));
	ViewMenuDescription = FText::FromString(TEXT("Dialogue graph editor"));
	ViewMenuTooltip = FText::FromString(TEXT("Shows current dialogue graph editor"));
}

TSharedRef<SWidget> CustomAssetEditorAppTabFactoryGraph::CreateTabBody(const FWorkflowTabSpawnInfo& InInfo) const
{
	const TSharedPtr<CustomAssetEditorApp> Application = App.Pin();

	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		.HAlign(HAlign_Fill)
		[
			SNew(SGraphEditor)
			.IsEditable(true)
			.GraphToEdit(Application->GetWorkingGraph())
		];
}

FText CustomAssetEditorAppTabFactoryGraph::GetTabToolTipText(const FWorkflowTabSpawnInfo& InInfo) const
{
	return FText::FromString(TEXT("Dialogue graph editor"));
}
