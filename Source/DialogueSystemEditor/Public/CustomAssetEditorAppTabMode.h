#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/ApplicationMode.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"

class CustomAssetEditorAppTabMode : public FApplicationMode
{
public:
	CustomAssetEditorAppTabMode(TSharedPtr<class CustomAssetEditorApp> InApp);
	
	virtual void RegisterTabFactories(TSharedPtr<class FTabManager> InTabManager) override;
	virtual void PreDeactivateMode() override;
	virtual void PostActivateMode() override;

private:
	TWeakPtr<CustomAssetEditorApp> App;
	FWorkflowAllowedTabSet TabsSet;
};