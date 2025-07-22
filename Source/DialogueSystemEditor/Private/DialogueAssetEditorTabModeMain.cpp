#include "DialogueAssetEditorTabModeMain.h"
#include "DialogueAssetEditorApp.h"
#include "DialogueAssetEditorTabFactoryProperties.h"
#include "DialogueAssetEditorTabFactoryGraph.h"

DialogueAssetEditorTabModeMain::DialogueAssetEditorTabModeMain(TSharedPtr<class DialogueAssetEditorApp> InApp) :
	FApplicationMode(TEXT("DialogueAssetEditorTabModeMain"))
{
	App = InApp;
	TabsSet.RegisterFactory(MakeShareable(new DialogueAssetEditorTabFactoryGraph(InApp)));
	TabsSet.RegisterFactory(MakeShareable(new DialogueAssetEditorTabFactoryProperties(InApp)));

	TabLayout = FTabManager::NewLayout("DialogueAssetEditor_TabModeMain_V1")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.75)
					->AddTab(FName(TEXT("DialogueAssetEditorTabFactoryGraph")), ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.25)
					->AddTab(FName(TEXT("DialogueAssetEditorTabFactoryProperties")), ETabState::OpenedTab)
				)
			)
		);
}

void DialogueAssetEditorTabModeMain::RegisterTabFactories(TSharedPtr<class FTabManager> InTabManager)
{
	TSharedPtr<DialogueAssetEditorApp> CurrApp = App.Pin();
	CurrApp->PushTabFactories(TabsSet);

	FApplicationMode::RegisterTabFactories(InTabManager);
}

void DialogueAssetEditorTabModeMain::PreDeactivateMode()
{
	FApplicationMode::PreDeactivateMode();
}

void DialogueAssetEditorTabModeMain::PostActivateMode()
{
	FApplicationMode::PostActivateMode();
}

