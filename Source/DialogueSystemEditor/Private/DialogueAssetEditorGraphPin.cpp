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

void SDialogueAssetEditorGraphPinStartOutput::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
}

FSlateColor SDialogueAssetEditorGraphPinStartOutput::GetPinColor() const
{
	return FSlateColor(FLinearColor(1.0f, 0.1f, 0.1f));
}

FDialogueAssetEditorGraphPinFactory::~FDialogueAssetEditorGraphPinFactory()
{
}

TSharedPtr<SGraphPin> FDialogueAssetEditorGraphPinFactory::CreatePin(class UEdGraphPin* InPin) const
{
	if (FName(TEXT("NodeDialogue")) == InPin->PinType.PinSubCategory)
	{
		return SNew(SDialogueAssetEditorGraphPin, InPin);
	}

	if (FName(TEXT("NodeStartOutput")) == InPin->PinType.PinSubCategory)
	{
		return SNew(SDialogueAssetEditorGraphPinStartOutput, InPin);
	}

	return nullptr;
}
