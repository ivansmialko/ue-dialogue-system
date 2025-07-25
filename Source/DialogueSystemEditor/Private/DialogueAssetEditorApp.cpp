#include "DialogueAssetEditorApp.h"
#include "DialogueAsset.h"
#include "DialogueGraph.h"
#include "DialogueAssetEditorTabModeMain.h"
#include "DialogueAssetEditorGraphSchema.h"

#include "Kismet2/BlueprintEditorUtils.h"

void DialogueAssetEditorApp::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	FWorkflowCentricApplication::RegisterTabSpawners(InTabManager);
}

void DialogueAssetEditorApp::InitEditor(const EToolkitMode::Type InMode, const TSharedPtr<class IToolkitHost>& InToolkitHost, UObject* InCustomAsset)
{
	TArray<UObject*> ObjectsToEdit;
	ObjectsToEdit.Add(InCustomAsset);

	InitAssetEditor(
		InMode,
		InToolkitHost,
		TEXT("CustomAssetEditor"),
		FTabManager::FLayout::NullLayout,
		true,
		true,
		ObjectsToEdit
	);

	WorkingAsset = Cast<UDialogueAsset>(InCustomAsset);
	WorkingGraph = FBlueprintEditorUtils::CreateNewGraph(WorkingAsset, NAME_None, UEdGraph::StaticClass(), UDialogueAssetEditorGraphSchema::StaticClass());

	AddApplicationMode(TEXT("DialogueAssetEditorTabModeMain"), MakeShareable(new DialogueAssetEditorTabModeMain(SharedThis(this))));
	SetCurrentMode(TEXT("DialogueAssetEditorTabModeMain"));
}

void DialogueAssetEditorApp::UpdateWorkingAsset() const
{
	if (!WorkingAsset)
		return;

	if (!WorkingGraph)
		return;

	UDialogueGraph* DialogueGraph = NewObject<UDialogueGraph>(WorkingAsset);
	WorkingAsset->Graph = DialogueGraph;

	TArray<std::pair<FGuid, FGuid>> Connections;
	TMap<FGuid, UDialogueGraphPin*>  IdToPinMap;

	for (UEdGraphNode* EditorNode : WorkingGraph->Nodes)
	{
		UDialogueGraphNode* GraphNode = NewObject<UDialogueGraphNode>(DialogueGraph);
		GrapNode->Position = FVector2D(EditorNode->NodePosX, EditorNode->NodePosY);

		for (UEdGraphPin* EditorNodePin : EditorNode->Pins)
		{
			UDialogueGraphPin* GraphPin = NewObject<UDialogueGraphPin>(GraphNode);
			GraphPin->Name = EditorNodePin->PinName;
			GraphPin->Id = EditorNodePin->PinId;

			if (EditorNodePin->HasAnyConnections() && EditorNodePin->Direction == EEdGraphPinDirection::EGPD_Output)
			{
				std::pair<FGuid, FGuid> Connection = std::make_pair(EditorNodePin->PinId, EditorNodePin->LinkedTo[0]->PinId);
				Connections.Add(Connection);
			}

			IdToPinMap[EditorNodePin->PinId] = GraphPin;
			if (EditorNodePin->Direction == EEdGraphPinDirection::EGPD_Input)
			{
				GraphPin->Input = EditorNodePin;
			}
		}
	}
}

void DialogueAssetEditorApp::UpdateWorkingGraph()
{

}
