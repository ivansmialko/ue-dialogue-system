#include "CustomAssetEditorAppTabFactory.h"
#include "CustomAssetEditorApp.h"

CustomAssetEditorAppTabFactory::CustomAssetEditorAppTabFactory(TSharedPtr<CustomAssetEditorApp> InApp):
	FWorkflowTabFactory(FName("CustomAssetEditorAppTab"), InApp)
{
	App = InApp;
	TabLabel = FText::FromString(TEXT("Primary"));
	ViewMenuDescription = FText::FromString(TEXT("Displays a primary view for whatever"));
	ViewMenuTooltip = FText::FromString(TEXT("Show the primary view"));
}

TSharedRef<SWidget> CustomAssetEditorAppTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& InInfo) const
{
	return SNew(STextBlock).Text(FText::FromString(TEXT("This is a text widget created for the custom tab")));
}

FText CustomAssetEditorAppTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& InInfo) const
{
	return FText::FromString(TEXT("A primary view for whatever"));
}
