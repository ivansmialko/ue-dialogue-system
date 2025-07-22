#pragma once
#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"

class DialogueAssetEditorTabFactoryGraph : public FWorkflowTabFactory
{
public:
	DialogueAssetEditorTabFactoryGraph(TSharedPtr<class DialogueAssetEditorApp> InApp);

	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& InInfo) const override;
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& InInfo) const override;

private:
	TWeakPtr<class DialogueAssetEditorApp> App;
};