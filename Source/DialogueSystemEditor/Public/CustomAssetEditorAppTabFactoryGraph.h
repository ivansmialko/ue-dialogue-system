#pragma once
#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"

class CustomAssetEditorAppTabFactoryGraph : public FWorkflowTabFactory
{
public:
	CustomAssetEditorAppTabFactoryGraph(TSharedPtr<class CustomAssetEditorApp> InApp);

	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& InInfo) const override;
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& InInfo) const override;

private:
	TWeakPtr<class CustomAssetEditorApp> App;
};