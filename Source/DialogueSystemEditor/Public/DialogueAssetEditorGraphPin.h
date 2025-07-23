#pragma once
#include "EdGraphUtilities.h"
#include "SGraphPin.h"

class SDialogueAssetEditorGraphPin : public SGraphPin
{
//public methods
public:
	SLATE_BEGIN_ARGS(SDialogueAssetEditorGraphPin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

//protected methods
protected:
	virtual FSlateColor GetPinColor() const override;
};

struct FDialogueAssetEditorGraphPinFactory : FGraphPanelPinFactory
{
//public methods
public:
	virtual ~FDialogueAssetEditorGraphPinFactory() override;
	virtual TSharedPtr<SGraphPin> CreatePin(class UEdGraphPin* InPin) const override;
};