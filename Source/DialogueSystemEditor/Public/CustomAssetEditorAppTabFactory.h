#pragma  once
#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"

class CustomAssetEditorAppTabFactory : FWorkflowTabFactory
{
public:
	CustomAssetEditorAppTabFactory(TSharedPtr<class UCustomAssetEditorApp> InApp);

	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& InInfo);
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& InInfo);

private:
	TWeakPtr<class CustomAssetEditorApp> App;
};