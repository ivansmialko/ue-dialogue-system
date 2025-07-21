#include "CustomAssetEditorAppTabFactoryProperties.h"
#include "CustomAssetEditorApp.h"
#include "CustomAsset.h"
#include "IDetailsView.h"
#include "PropertyEditorModule.h"

CustomAssetEditorAppTabFactoryProperties::CustomAssetEditorAppTabFactoryProperties(TSharedPtr<CustomAssetEditorApp> InApp):
	FWorkflowTabFactory(FName("CustomAssetEditorAppTabFactoryProperties"), InApp)
{
	App = InApp;
	TabLabel = FText::FromString(TEXT("Properties"));
	ViewMenuDescription = FText::FromString(TEXT("Current object properties"));
	ViewMenuTooltip = FText::FromString(TEXT("Shows current object properties"));
}

TSharedRef<SWidget> CustomAssetEditorAppTabFactoryProperties::CreateTabBody(const FWorkflowTabSpawnInfo& InInfo) const
{
	const TSharedPtr<CustomAssetEditorApp> Application = App.Pin();
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));

	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.bAllowSearch = false;
	DetailsViewArgs.bHideSelectionTip = true;
	DetailsViewArgs.bLockable = false;
	DetailsViewArgs.bSearchInitialKeyFocus = true;
	DetailsViewArgs.bUpdatesFromSelection = false;
	DetailsViewArgs.NotifyHook = nullptr;
	DetailsViewArgs.bShowOptions = true;
	DetailsViewArgs.bShowModifiedPropertiesOption = false;
	DetailsViewArgs.bShowScrollBar = false;

	const TSharedPtr<IDetailsView> DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObject(Application->GetWorkingAsset());

	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		.HAlign(HAlign_Fill)
		[
			DetailsView.ToSharedRef()
		];
}

FText CustomAssetEditorAppTabFactoryProperties::GetTabToolTipText(const FWorkflowTabSpawnInfo& InInfo) const
{
	return FText::FromString(TEXT("Current object properties"));
}
