#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/ApplicationMode.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"

class DialogueAssetEditorTabModeMain : public FApplicationMode
{
public:
	DialogueAssetEditorTabModeMain(TSharedPtr<class DialogueAssetEditorApp> InApp);
	
	virtual void RegisterTabFactories(TSharedPtr<class FTabManager> InTabManager) override;
	virtual void PreDeactivateMode() override;
	virtual void PostActivateMode() override;

private:
	TWeakPtr<DialogueAssetEditorApp> App;
	FWorkflowAllowedTabSet TabsSet;
};