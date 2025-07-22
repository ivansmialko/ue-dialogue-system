#include "DialogueAssetEditorTabFactoryProperties.h"
#include "DialogueAssetEditorApp.h"
#include "DialogueAsset.h"
#include "IDetailsView.h"
#include "PropertyEditorModule.h"

DialogueAssetEditorTabFactoryProperties::DialogueAssetEditorTabFactoryProperties(TSharedPtr<DialogueAssetEditorApp> InApp):
	FWorkflowTabFactory(FName("DialogueAssetEditorTabFactoryProperties"), InApp)
{
	App = InApp;
	TabLabel = FText::FromString(TEXT("Properties"));
	ViewMenuDescription = FText::FromString(TEXT("Current object properties"));
	ViewMenuTooltip = FText::FromString(TEXT("Shows current object properties"));
}

TSharedRef<SWidget> DialogueAssetEditorTabFactoryProperties::CreateTabBody(const FWorkflowTabSpawnInfo& InInfo) const
{
	const TSharedPtr<DialogueAssetEditorApp> Application = App.Pin();
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

FText DialogueAssetEditorTabFactoryProperties::GetTabToolTipText(const FWorkflowTabSpawnInfo& InInfo) const
{
	return FText::FromString(TEXT("Current object properties"));
}
