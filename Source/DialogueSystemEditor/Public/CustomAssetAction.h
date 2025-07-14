#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

class CustomAssetAction : public FAssetTypeActions_Base
{
public:
	CustomAssetAction(EAssetTypeCategories::Type InCategory);

//Begin FAssetTypeActions_Base interface
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
	virtual uint32 GetCategories();
//End FAssetTypeActions_Base interface

private:
	EAssetTypeCategories::Type AssetCategory;
};