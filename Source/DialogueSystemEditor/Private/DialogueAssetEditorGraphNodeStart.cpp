#include "DialogueAssetEditorGraphNodeStart.h"

UEdGraphPin* UDialogueAssetEditorGraphNodeStart::CreateDialoguePin(const EEdGraphPinDirection& InDirection,
	FName InName)
{
	FName Category = TEXT("Outputs");
	FName SubCategory = TEXT("NodeStartOutput");

	UEdGraphPin* Pin = CreatePin(InDirection, Category, InName);
	Pin->PinType.PinSubCategory = SubCategory;

	return Pin;
}
