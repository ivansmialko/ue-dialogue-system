#include "CustomAssetEditorAppTabMode.h"
#include "CustomAssetEditorApp.h"
#include "CustomAssetEditorAppTabFactoryProperties.h"
#include "CustomAssetEditorAppTabFactoryGraph.h"

CustomAssetEditorAppTabMode::CustomAssetEditorAppTabMode(TSharedPtr<class CustomAssetEditorApp> InApp) :
	FApplicationMode(TEXT("CustomAssetEditorAppTabMode"))
{
	App = InApp;
	TabsSet.RegisterFactory(MakeShareable(new CustomAssetEditorAppTabFactoryGraph(InApp)));
	TabsSet.RegisterFactory(MakeShareable(new CustomAssetEditorAppTabFactoryProperties(InApp)));

	TabLayout = FTabManager::NewLayout("CustomAssetEditorAppTabMode_Layout_V1")
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
					->AddTab(FName(TEXT("CustomAssetEditorAppTabFactoryGraph")), ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.25)
					->AddTab(FName(TEXT("CustomAssetEditorAppTabFactoryProperties")), ETabState::OpenedTab)
				)
			)
		);
}

void CustomAssetEditorAppTabMode::RegisterTabFactories(TSharedPtr<class FTabManager> InTabManager)
{
	TSharedPtr<CustomAssetEditorApp> CurrApp = App.Pin();
	CurrApp->PushTabFactories(TabsSet);

	FApplicationMode::RegisterTabFactories(InTabManager);
}

void CustomAssetEditorAppTabMode::PreDeactivateMode()
{
	FApplicationMode::PreDeactivateMode();
}

void CustomAssetEditorAppTabMode::PostActivateMode()
{
	FApplicationMode::PostActivateMode();
}

