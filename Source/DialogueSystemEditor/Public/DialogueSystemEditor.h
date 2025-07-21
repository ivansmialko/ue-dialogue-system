// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

#include "CustomAssetAction.h"
#include "Styling/SlateStyleRegistry.h"

class FDialogueSystemEditorModule : public IModuleInterface
{
//private fields
private:
	TSharedPtr<FSlateStyleSet> StyleSet{ nullptr };

//public methods
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
