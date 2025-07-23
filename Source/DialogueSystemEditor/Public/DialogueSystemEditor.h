// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

#include "DialogueAssetAction.h"
#include "Styling/SlateStyleRegistry.h"

struct FDialogueAssetEditorGraphPinFactory;

class FDialogueSystemEditorModule : public IModuleInterface
{
//private fields
private:
	TSharedPtr<FSlateStyleSet> StyleSet{ nullptr };
	TSharedPtr<FDialogueAssetEditorGraphPinFactory> GraphNodePinFactory;

//public methods
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
