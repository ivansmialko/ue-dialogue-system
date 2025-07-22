#pragma once
#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"

class DialogueAssetEditorTabFactoryProperties : public FWorkflowTabFactory
{
public:
	DialogueAssetEditorTabFactoryProperties(TSharedPtr<class DialogueAssetEditorApp> InApp);

	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& InInfo) const override;
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& InInfo) const override;

private:
	TWeakPtr<class DialogueAssetEditorApp> App;
};