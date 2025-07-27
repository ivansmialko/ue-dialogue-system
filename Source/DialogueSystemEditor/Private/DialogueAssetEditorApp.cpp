#include "DialogueAssetEditorApp.h"
#include "DialogueAsset.h"
#include "DialogueAssetEditorGraphNode.h"
#include "DialogueAssetEditorGraphNodeStart.h"
#include "DialogueGraph.h"
#include "DialogueAssetEditorTabModeMain.h"
#include "DialogueAssetEditorGraphSchema.h"

#include "Kismet2/BlueprintEditorUtils.h"

DEFINE_LOG_CATEGORY_STATIC(DialogueAssetEditorAppSub, Log, All)

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
	WorkingAsset->SetPreSaveListener([this]() { OnWorkingAssetPreSave(); });

	WorkingGraph = FBlueprintEditorUtils::CreateNewGraph(WorkingAsset, NAME_None, UEdGraph::StaticClass(), UDialogueAssetEditorGraphSchema::StaticClass());

	AddApplicationMode(TEXT("DialogueAssetEditorTabModeMain"), MakeShareable(new DialogueAssetEditorTabModeMain(SharedThis(this))));
	SetCurrentMode(TEXT("DialogueAssetEditorTabModeMain"));

	UpdateWorkingGraph();
}

void DialogueAssetEditorApp::OnWorkingAssetPreSave() const
{
	//Update working asset from the graph just before saving it
	UpdateWorkingAsset();
}

void DialogueAssetEditorApp::OnGraphSelectionHandler(const FGraphPanelSelectionSet& InSelection) const
{
	const UDialogueAssetEditorGraphNode* SelectedNode = GetSelectedNode(InSelection);
	SelectedNodeDetailsView->SetObject(SelectedNode ? SelectedNode->GetNodeData() : nullptr);
}

void DialogueAssetEditorApp::OnNodeDetailsViewUpdated(const FPropertyChangedEvent& InEvent) const
{
	if (!WorkingGraphUi)
		return;

	UDialogueAssetEditorGraphNode* SelectedNode = GetSelectedNode(WorkingGraphUi->GetSelectedNodes());
	if (!SelectedNode)
		return;

	SelectedNode->SyncPinsWithResponses();

	WorkingGraphUi->NotifyGraphChanged();
}

void DialogueAssetEditorApp::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	FWorkflowCentricApplication::RegisterTabSpawners(InTabManager);
}

void DialogueAssetEditorApp::OnClose()
{
	UpdateWorkingAsset();
	WorkingAsset->SetPreSaveListener(nullptr);

	FAssetEditorToolkit::OnClose();
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

	//Read all the nodes and pins from editor graph, create runtime nodes
	for (UEdGraphNode* EditorNode : WorkingGraph->Nodes)
	{
		UDialogueGraphNode* GraphNode = NewObject<UDialogueGraphNode>(DialogueGraph);
		GraphNode->Position = FVector2D(EditorNode->NodePosX, EditorNode->NodePosY);

		for (UEdGraphPin* EditorNodePin : EditorNode->Pins)
		{
			UDialogueGraphPin* GraphPin = NewObject<UDialogueGraphPin>(GraphNode);
			GraphPin->Name = EditorNodePin->PinName;
			GraphPin->Id = EditorNodePin->PinId;

			switch (EditorNodePin->Direction)
			{
			case EGPD_Input:
			{
				if (!GraphNode->Input)
				{
					GraphNode->Input = GraphPin;
				}
			} break;
			case EGPD_Output:
			{
				if (EditorNodePin->HasAnyConnections())
				{
					std::pair<FGuid, FGuid> Connection = std::make_pair(EditorNodePin->PinId, EditorNodePin->LinkedTo[0]->PinId);
					Connections.Add(Connection);
				}

				GraphNode->Outputs.Add(GraphPin);
			} break;
			default: break;
			}

			if (EditorNode->IsA(UDialogueAssetEditorGraphNode::StaticClass()))
			{
				const UDialogueAssetEditorGraphNode* DialogueEditorNode = Cast<UDialogueAssetEditorGraphNode>(EditorNode);
				GraphNode->Type = EDialogueNode::EDN_Dialogue;
				GraphNode->Data = DialogueEditorNode->GetNodeData();
			}
			else if (EditorNode->IsA(UDialogueAssetEditorGraphNodeStart::StaticClass()))
			{
				GraphNode->Type = EDialogueNode::EDN_Start;
			}

			IdToPinMap.Add(EditorNodePin->PinId, GraphPin);
		}

		DialogueGraph->Nodes.Add(GraphNode);
	}

	//Set-up connections between pins
	for (const auto& [IdPinA, IdPinB] : Connections)
	{
		UDialogueGraphPin* PinA = IdToPinMap[IdPinA];
		UDialogueGraphPin* PinB = IdToPinMap[IdPinB];

		PinA->Connection = PinB;
	}
}

void DialogueAssetEditorApp::UpdateWorkingGraph() const
{
	if (!WorkingGraph)
		return;

	if (!WorkingAsset)
		return;

	if (!WorkingAsset->Graph)
	{
		WorkingGraph->GetSchema()->CreateDefaultNodesForGraph(*WorkingGraph);
		return;
	}

	TArray<std::pair<FGuid, FGuid>> Connections;
	TMap<FGuid, UEdGraphPin*> IdToPinMap;

	//Read all the nodes and pins from runtime graph, build editor graph nodes
	for (const UDialogueGraphNode* GraphNode : WorkingAsset->Graph->Nodes)
	{
		UDialogueAssetEditorGraphNodeBase* EditorNode{ nullptr };

		switch (GraphNode->Type)
		{
		case EDialogueNode::EDN_Start:
			EditorNode = NewObject<UDialogueAssetEditorGraphNodeStart>(WorkingGraph);
			break;
		case EDialogueNode::EDN_Dialogue:
			EditorNode = NewObject<UDialogueAssetEditorGraphNodeStart>(WorkingGraph);
			break;
		case EDialogueNode::EDN_End:
			break;
		default:
			UE_LOG(DialogueAssetEditorAppSub, Error, TEXT("DialogueAssetEditorApp::UpdateWorkingGraph() Unknown node type"))
		}

		EditorNode->CreateNewGuid();
		EditorNode->NodePosX = GraphNode->Position.X;
		EditorNode->NodePosY = GraphNode->Position.Y;

		if (GraphNode->Type == EDialogueNode::EDN_Dialogue)
		{
			if (GraphNode->Data)
			{
				EditorNode->SetNodeData(DuplicateObject(GraphNode->Data, EditorNode));
			}
			else
			{
				EditorNode->SetNodeData(NewObject<UDialogueNodeData>(EditorNode));
			}
		}

		//Build input pin, record connection
		if (UDialogueGraphPin* GraphNodeInputPin = GraphNode->Input)
		{
			UEdGraphPin* EditorNodePin = EditorNode->CreateDialoguePin(EEdGraphPinDirection::EGPD_Input, GraphNodeInputPin->Name);
			EditorNodePin->PinId = GraphNodeInputPin->Id;

			if (GraphNodeInputPin->Connection)
			{
				Connections.Add(std::make_pair(GraphNodeInputPin->Id, GraphNodeInputPin->Connection->Id));
			}

			IdToPinMap.Add(GraphNodeInputPin->Id, EditorNodePin);
		}

		//Build output pins, record connections
		for (const UDialogueGraphPin* GraphNodeOutputPin : GraphNode->Outputs)
		{
			UEdGraphPin* EditorNodePin = EditorNode->CreateDialoguePin(EEdGraphPinDirection::EGPD_Output, GraphNodeOutputPin->Name);
			EditorNodePin->PinId = GraphNodeOutputPin->Id;

			if (GraphNodeOutputPin->Connection)
			{
				Connections.Add(std::make_pair(GraphNodeOutputPin->Id, GraphNodeOutputPin->Connection->Id));
			}

			IdToPinMap.Add(GraphNodeOutputPin->Id, EditorNodePin);
		}

		WorkingGraph->AddNode(EditorNode);
	}

	//Set-up connections between pins
	for (const auto& [IdPinA, IdPinB] : Connections)
	{
		UEdGraphPin* PinA = IdToPinMap[IdPinA];
		UEdGraphPin* PinB = IdToPinMap[IdPinB];

		PinA->LinkedTo.Add(PinB);
		PinB->LinkedTo.Add(PinA);
	}
}

// ReSharper disable once CppMemberFunctionMayBeStatic
UDialogueAssetEditorGraphNode* DialogueAssetEditorApp::GetSelectedNode(const FGraphPanelSelectionSet& InSelection) const
{
	//Find the first graph node if any
	for (UObject* Object : InSelection)
	{
		UDialogueAssetEditorGraphNode* EditorNode = Cast<UDialogueAssetEditorGraphNode>(Object);
		if (!EditorNode)
			continue;

		return EditorNode;
	}

	return nullptr;
}

void DialogueAssetEditorApp::SetSelectedNodeDetailView(const TSharedPtr<IDetailsView>& InDetailsView)
{
	SelectedNodeDetailsView = InDetailsView;
	SelectedNodeDetailsView->OnFinishedChangingProperties().AddRaw(this, &DialogueAssetEditorApp::OnNodeDetailsViewUpdated);
}
