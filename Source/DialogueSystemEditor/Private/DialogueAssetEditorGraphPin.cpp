#include "DialogueAssetEditorGraphPin.h"
#include "KismetPins/SGraphPinColor.h"
#include "EdGraph/EdGraphPin.h"

void SDialogueAssetEditorGraphPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
}

FSlateColor SDialogueAssetEditorGraphPin::GetPinColor() const
{
	return FSlateColor(FLinearColor(0.2f, 1.0f, 0.2f));
}

FDialogueAssetEditorGraphPinFactory::~FDialogueAssetEditorGraphPinFactory()
{
}

TSharedPtr<SGraphPin> FDialogueAssetEditorGraphPinFactory::CreatePin(class UEdGraphPin* InPin) const
{
	if (FName(TEXT("CustomPin")) == InPin->PinType.PinSubCategory)
	{
		return SNew(SDialogueAssetEditorGraphPin, InPin);
	}

	return nullptr;
}
