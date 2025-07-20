#include "CustomAssetEditorAppTabMode.h"
#include "CustomAssetEditorApp.h"
#include "CustomAssetEditorAppTabFactory.h"

CustomAssetEditorAppTabMode::CustomAssetEditorAppTabMode(TSharedPtr<class CustomAssetEditorApp> InApp) :
	FApplicationMode(TEXT("CustomAssetEditorAppTabMode"))
{
	App = InApp;
	TabsSet.RegisterFactory(MakeShareable(new CustomAssetEditorAppTabFactory(InApp)));

	TabLayout = FTabManager::NewLayout("CustomAssetEditorAppTabMode_Layout_V1")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->AddTab(FName(TEXT("CustomAssetEditorAppTab")), ETabState::OpenedTab)
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

