// Fill out your copyright notice in the Description page of Project Settings.


#include "FlowEditor.h"
#include "SDockTab.h"
#include "GenericCommands.h"
#include "BlueprintEditorUtils.h"
#include "EdGraphUtilities.h"
#include "Engine/Blueprint.h"
#include "QuestsEditor/Editor/Graph/UnrealEd_QuestGraph.h"
#include "ScopedTransaction.h"
#include "UnrealEd_QuestEditorSchema.h"
#include "QuestsEditor/Editor/Graph/UnrealEd_QuestPinNodes.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "SNodePanel.h"
#include "BlueprintEditorModule.h"
#include "GraphEditorActions.h"
#include "Kismet2NameValidators.h"
#include "PropertyEditorModule.h"
#include "Misc/NodeCompiler.h"
#include "Misc/BlueprintScript/BlueprintScriptManager.h"
#include "Quests/GenericTypes/Quest.h"


/*Quest System Base Editor*/
FLinearColor FQuestSystemBaseEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor();
}

FString FQuestSystemBaseEditor::GetWorldCentricTabPrefix() const
{
	return FString();
}

void FQuestSystemBaseEditor::InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UObject * PropData,TSubclassOf<UEdGraphSchema> Schema)
{

	FAssetEditorManager::Get().CloseOtherEditors(PropData, this);
	PropEdited = PropData;

	UQuestBase* Base = Cast<UQuestBase>(PropData);
	if (!Base->QuestGraph)
	{
		UEdGraph* CustGraph = FBlueprintEditorUtils::CreateNewGraph(PropEdited, NAME_None, UnrealEd_BaseQuestGraph::StaticClass(), Schema);
		Base->QuestGraph = CustGraph;
	}
	UEdGraph* Graph = Base->QuestGraph;
	
	GraphEditor = CreateGraphEditorWidget(Graph);
	

	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("CustomEditor_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->SetHideTabWell(true)
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Horizontal)
				->SetSizeCoefficient(0.2f)
				->Split
				(

					FTabManager::NewStack()
					->SetSizeCoefficient(0.8f)
					->SetHideTabWell(true)
					->AddTab(FName("Viewport"), ETabState::OpenedTab)

				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.2f)
					->SetHideTabWell(true)
					->AddTab(FName("Details"), ETabState::OpenedTab)
				)


			)

		);




	MyToolBarCommands = MakeShareable(new FUICommandList);
	MyToolBarCommands->MapAction(FToolBarCommandsCommands::Get().BPScript,
		FExecuteAction::CreateSP(this, &FQuestSystemBaseEditor::OpenBlueprintEditor)
	);
	MyToolBarCommands->MapAction(FToolBarCommandsCommands::Get().PackageNode,
        FExecuteAction::CreateSP(this, &FQuestSystemBaseEditor::PackageGraph)
    );
	ToolbarExtender = MakeShareable(new FExtender);
	ToolbarExtender->AddToolBarExtension("Asset", EExtensionHook::After, MyToolBarCommands, FToolBarExtensionDelegate::CreateRaw(this, &FQuestSystemBaseEditor::AddToolbarExtension));
	AddToolbarExtender(ToolbarExtender);
	// Initialize the asset editor and spawn nothing (dummy layout)
	InitAssetEditor(Mode, InitToolkitHost, FName(TEXT("CustomEditorApp")), StandaloneDefaultLayout, true, true, Graph->GetOuter());
	
	CreateStartEndPins(Graph);
}

void FQuestSystemBaseEditor::OpenBlueprintEditor()
{
	FBlueprintScriptManager::Get().OpenBlueprintForObject(Cast<UQuestBase>(PropEdited));
}

void FQuestSystemBaseEditor::PackageGraph()
{
	UnrealEd_BaseQuestGraph* Graph = Cast<UnrealEd_BaseQuestGraph>(GraphEditor->GetCurrentGraph());
	
	FNodeCompiler::Get().PackageGraph(Graph);
}

UBlueprint * FQuestSystemBaseEditor::CreateBlueprintScript()
{
	return nullptr;
}

void FQuestSystemBaseEditor::RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager)
{
	WorkspaceMenuCategory = TabManager->AddLocalWorkspaceMenuCategory(FText::FromString("Custom Editor"));
	auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners(TabManager);

	TabManager->RegisterTabSpawner(FName("Viewport"), FOnSpawnTab::CreateSP(this, &FQuestSystemBaseEditor::SpawnTab_Viewport))
		.SetDisplayName(FText::FromString("Viewport"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Viewports"));

	TabManager->RegisterTabSpawner(FName("Details"), FOnSpawnTab::CreateSP(this, &FQuestSystemBaseEditor::SpawnTab_Details))
		.SetDisplayName(FText::FromString("Details"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));
}

void FQuestSystemBaseEditor::UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager)
{
}

TSharedRef<SDockTab> FQuestSystemBaseEditor::SpawnTab_Viewport(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.Label(FText::FromString("Node Graph"))
		.TabColorScale(GetTabColorScale())
		[
			GraphEditor.ToSharedRef()
		];

}

TSharedRef<SDockTab> FQuestSystemBaseEditor::SpawnTab_Details(const FSpawnTabArgs& Args)
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	const FDetailsViewArgs DetailsViewArgs(false, false, true, FDetailsViewArgs::HideNameArea, true, this);
	TSharedRef<IDetailsView> PropertyEditorRef = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	PropertyEditor = PropertyEditorRef;

	PropertyEditor->SetObject(PropEdited, true);

	// Spawn the tab
	return SNew(SDockTab)
		.Label(FText::FromString("Details"))
		[
			PropertyEditorRef
		];
}
void FQuestSystemBaseEditor::AddToolbarExtension(FToolBarBuilder & builder)
{
	FSlateIcon Icon = FSlateIcon(TEXT("EditorStyle"), "FullBlueprintEditor.EditGlobalOptions");
	builder.AddToolBarButton(FToolBarCommandsCommands::Get().BPScript, NAME_None, FText::FromString("Open Blueprint"),FText::FromString("Opens Blueprint class with generated events for this type"),Icon);
	FSlateIcon PackageIcon = FSlateIcon(TEXT("EditorStyle"),"MaterialEditor.ToggleRealtimeExpressions");
	builder.AddToolBarButton(FToolBarCommandsCommands::Get().PackageNode,NAME_None, FText::FromString("Package Graph"),FText::FromString("Packages Graph Execution into Object"),PackageIcon);
}
void FQuestSystemBaseEditor::CreateStartEndPins(UEdGraph * InGraph)
{
	TArray<UQuestStartNode*> StartNodes;
	InGraph->GetNodesOfClass<UQuestStartNode>(StartNodes);

	TArray<UQuestEndNode*> EndNodes;
	InGraph->GetNodesOfClass<UQuestEndNode>(EndNodes);

	if (StartNodes.Num() == 0)
		InGraph->AddNode(CreateGraphNode(InGraph, UQuestStartNode::StaticClass(), FVector2D(-100, 0)));
	if(EndNodes.Num() == 0)
		InGraph->AddNode(CreateGraphNode(InGraph, UQuestEndNode::StaticClass(), FVector2D(100, 0)));
}
TSharedRef<SGraphEditor> FQuestSystemBaseEditor::CreateGraphEditorWidget(UEdGraph* InGraph)
{
	// Create the appearance info
	FGraphAppearanceInfo AppearanceInfo;
	AppearanceInfo.CornerText = FText::FromString(PropEdited->GetClass()->GetName());
	GraphEditorCommands = MakeShareable(new FUICommandList);
	{
		GraphEditorCommands->MapAction(FGenericCommands::Get().SelectAll,
			FExecuteAction::CreateSP(this, &FQuestSystemBaseEditor::SelectAllNodes),
			FCanExecuteAction::CreateSP(this, &FQuestSystemBaseEditor::CanSelectAllNodes)
		);

		GraphEditorCommands->MapAction(FGenericCommands::Get().Delete,
			FExecuteAction::CreateSP(this, &FQuestSystemBaseEditor::DeleteSelectedNodes),
			FCanExecuteAction::CreateSP(this, &FQuestSystemBaseEditor::CanDeleteNodes)
		);

		GraphEditorCommands->MapAction(FGenericCommands::Get().Copy,
			FExecuteAction::CreateSP(this, &FQuestSystemBaseEditor::CopySelectedNodes),
			FCanExecuteAction::CreateSP(this, &FQuestSystemBaseEditor::CanCopyNodes)
		);

		GraphEditorCommands->MapAction(FGenericCommands::Get().Paste,
			FExecuteAction::CreateSP(this, &FQuestSystemBaseEditor::PasteNodes),
			FCanExecuteAction::CreateSP(this, &FQuestSystemBaseEditor::CanPasteNodes)
		);

		GraphEditorCommands->MapAction(FGenericCommands::Get().Cut,
			FExecuteAction::CreateSP(this, &FQuestSystemBaseEditor::CutSelectedNodes),
			FCanExecuteAction::CreateSP(this, &FQuestSystemBaseEditor::CanCutNodes)
		);

		GraphEditorCommands->MapAction(FGenericCommands::Get().Duplicate,
			FExecuteAction::CreateSP(this, &FQuestSystemBaseEditor::DuplicateNodes),
			FCanExecuteAction::CreateSP(this, &FQuestSystemBaseEditor::CanDuplicateNodes)
		);

		GraphEditorCommands->MapAction( FGenericCommands::Get().Rename,
                FExecuteAction::CreateSP( this, &FQuestSystemBaseEditor::RenameNodes)
                );




		GraphEditorCommands->MapAction( FGraphEditorCommands::Get().CreateComment,
            FExecuteAction::CreateSP( this, &FQuestSystemBaseEditor::CreateComment )
            );
                

	}

	SGraphEditor::FGraphEditorEvents InEvents;
	InEvents.OnSelectionChanged = SGraphEditor::FOnSelectionChanged::CreateSP(this, &FQuestSystemBaseEditor::OnSelectedNodesChanged);
	InEvents.OnNodeDoubleClicked = FSingleNodeEvent::CreateSP(this, &FQuestSystemBaseEditor::OnNodeDoubleClicked);
	InEvents.OnTextCommitted = FOnNodeTextCommitted::CreateSP(this,&FQuestSystemBaseEditor::OnNodeTitleChanged);

	
	TSharedRef<SGraphEditor> _GraphEditor = SNew(SGraphEditor)
		.AdditionalCommands(GraphEditorCommands)
		.Appearance(AppearanceInfo)
		.GraphToEdit(InGraph)
		.GraphEvents(InEvents)
		;
	return _GraphEditor;
}

UEdGraphNode* FQuestSystemBaseEditor::CreateGraphNode(class UEdGraph* ParentGraph, TSubclassOf<UEdGraphNode> Class,const FVector2D Location)
{
	if (ParentGraph == NULL) return NULL;
	UEdGraphNode* ResultNode = NewObject<UEdGraphNode>(ParentGraph,Class);
	ParentGraph->Modify();
	ResultNode->SetFlags(RF_Transactional);
	// set outer to be the graph so it doesn't go away
	ResultNode->Rename(NULL, ParentGraph, REN_NonTransactional);
	ResultNode->CreateNewGuid();
	ResultNode->NodePosX = Location.X;
	ResultNode->NodePosY = Location.Y;
	// setup pins after placing node
	ResultNode->AllocateDefaultPins();
	return ResultNode;
}

void FQuestSystemBaseEditor::OnGraphChanged(const FEdGraphEditAction & Action)
{
}

void FQuestSystemBaseEditor::SelectAllNodes()
{
}

bool FQuestSystemBaseEditor::CanSelectAllNodes() const
{
	return true;
}

void FQuestSystemBaseEditor::DeleteSelectedNodes()
{
	TArray<UEdGraphNode*> NodesToDelete;
	const FGraphPanelSelectionSet SelectedNodes = GraphEditor->GetSelectedNodes();

	for (FGraphPanelSelectionSet::TConstIterator NodeIt(SelectedNodes); NodeIt; ++NodeIt)
	{
		NodesToDelete.Add(CastChecked<UEdGraphNode>(*NodeIt));
	}

	DeleteNodes(NodesToDelete);
}

bool FQuestSystemBaseEditor::CanDeleteNode(UEdGraphNode * Node)
{
	if (Node->IsA(UQuestEndNode::StaticClass()) || Node->IsA(UQuestStartNode::StaticClass()))
		return false;
	return true;
}

bool FQuestSystemBaseEditor::CanDeleteNodes() const
{
	return true;
}

void FQuestSystemBaseEditor::DeleteNodes(const TArray<class UEdGraphNode*>& NodesToDelete)
{
	if (NodesToDelete.Num() > 0)
	{

		for (int32 Index = 0; Index < NodesToDelete.Num(); ++Index)
		{
			if (!CanDeleteNode(NodesToDelete[Index])) {
				continue;
			}

			// Break all node links first so that we don't update the material before deleting
			NodesToDelete[Index]->BreakAllNodeLinks();

			FBlueprintEditorUtils::RemoveNode(NULL, NodesToDelete[Index], true);

			// TODO: Process deletion in the data model
		}
	}
}

void FQuestSystemBaseEditor::CopySelectedNodes()
{
}

bool FQuestSystemBaseEditor::CanCopyNodes() const
{
	return false;
}

void FQuestSystemBaseEditor::PasteNodes()
{
}

void FQuestSystemBaseEditor::PasteNodesHere(const FVector2D & Location)
{
}

bool FQuestSystemBaseEditor::CanPasteNodes() const
{
	return false;
}

void FQuestSystemBaseEditor::CutSelectedNodes()
{
}

bool FQuestSystemBaseEditor::CanCutNodes() const
{
	return false;
}

void FQuestSystemBaseEditor::DuplicateNodes()
{
}

bool FQuestSystemBaseEditor::CanDuplicateNodes() const
{
	return false;
}

void FQuestSystemBaseEditor::DeleteSelectedDuplicatableNodes()
{
}

void FQuestSystemBaseEditor::RenameNodes()
{
}

void FQuestSystemBaseEditor::OnNodeTitleChanged(const FText& NewText, ETextCommit::Type CommitInfo,
	UEdGraphNode* NodeBeingChanged)
{
	if(NodeBeingChanged->IsValidLowLevel())
	{
		NodeBeingChanged->Modify();
		NodeBeingChanged->OnRenameNode(NewText.ToString());
	}
}

bool FQuestSystemBaseEditor::OnNodeTitleVerification(const FText& NewText, UEdGraphNode* NodeBeingChanged,
	FText& OutErrorMessage)
{
	bool Result = 0;
	TSharedPtr<INameValidatorInterface> NameValidator = NodeBeingChanged->MakeNameValidator();
	if(NodeBeingChanged->IsValidLowLevel() && NodeBeingChanged->bCanRenameNode)
	{
		NodeBeingChanged->ErrorMsg.Empty();

		EValidatorResult ValidatorResult = NameValidator->IsValid(NewText.ToString(),true);

		if(ValidatorResult == EValidatorResult::Ok) Result = true;
	}
	return Result;
}

void FQuestSystemBaseEditor::CreateComment()
{
	if (GraphEditor.IsValid())
	{
		if (UEdGraph* Graph = GraphEditor->GetCurrentGraph())
		{

			FQuestEdGraphAction_AddComment CommentAction;
			CommentAction.PerformAction(Graph, NULL, GraphEditor->GetPasteLocation(),false);	
			
		}
	}
}

void FQuestSystemBaseEditor::OnSelectedNodesChanged(const TSet<class UObject*>& NewSelection)
{
	TArray<UObject*> SelectedObjects;
	for (UObject* Object : NewSelection)
	{
		SelectedObjects.Add(Object);
		UE_LOG(LogTemp, Warning, TEXT("Selected Node,  %s"), *Object->GetClass()->GetName());
	}

	if (SelectedObjects.Num() == 0)
	{
		PropertyEditor->SetObject(PropEdited, true);
		return;
	}

	PropertyEditor->SetObject(SelectedObjects[0]);
	if (SelectedObjects[0]->IsA(UQuestBaseNode::StaticClass()))
	{
		IQuestBaseInterface* Owner = Cast<UQuestBaseNode>(SelectedObjects[0])->GetOwner();
		if (Owner)
			PropertyEditor->SetObject(Owner->_getUObject());
		else
			PropertyEditor->SetObject(SelectedObjects[0]);
	}
}

void FQuestSystemBaseEditor::OnNodeDoubleClicked(UEdGraphNode * Node)
{
	if(Node->IsA(UQuestObjectiveNode::StaticClass()))
	{
		FAssetEditorManager::Get().OpenEditorForAsset((UObjective*)Cast<UQuestBaseNode>(Node)->Owner.GetObject());
	}
}

