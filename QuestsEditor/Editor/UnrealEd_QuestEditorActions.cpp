// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealEd_QuestEditorActions.h"
#include "Toolkits/ToolkitManager.h"


//Add Node Context
UEdGraphNode* FAddNodeContextAction::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin,
	const FVector2D Location, bool bSelectNewNode)
{
	UEdGraphNode* ResultNode = NewObject<UEdGraphNode>(ParentGraph, NodeClass);
	
	return FEdGraphSchemaAction_NewNode::SpawnNodeFromTemplate<UEdGraphNode>(ParentGraph,ResultNode,Location,bSelectNewNode);
}
//Objective Context
UEdGraphNode * FObjectiveContextAction::PerformAction(UEdGraph * ParentGraph, UEdGraphPin * FromPin, const FVector2D Location, bool bSelectNewNode)
{
	NodeClass = UQuestObjectiveNode::StaticClass();
	UQuestObjectiveNode* ResultNode = Cast<UQuestObjectiveNode>(FAddNodeContextAction::PerformAction(ParentGraph, FromPin, Location, bSelectNewNode));
	ResultNode->Owner = NodeTemplate;
	return ResultNode;
}

//Scriptable Object
UEdGraphNode* FScriptableObjectContextAction::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin,
	const FVector2D Location, bool bSelectNewNode)
{

	UScriptableNode* Node = (UScriptableNode*)FAddNodeContextAction::PerformAction(ParentGraph, FromPin, Location, bSelectNewNode);
	Node->ScriptableObject = Cast<AScriptableObject>(Actor);
	return Node;
}
//Bp Executor
UEdGraphNode * FBPExecutorContextAction::PerformAction(UEdGraph * ParentGraph, UEdGraphPin * FromPin, const FVector2D Location, bool bSelectNewNode)
{
	UEventExecutorNode* Node = Cast<UEventExecutorNode>(FAddNodeContextAction::PerformAction(ParentGraph, FromPin, Location, bSelectNewNode));

	//Node->FunctionToExecute = Function;
	Node->ReloadFunctions();
	return Node;
}


// Comment Action
UEdGraphNode* FQuestEdGraphAction_AddComment::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode)
{
	UEdGraphNode_Comment* CommentNode = NewObject<UEdGraphNode_Comment>();

	TSharedPtr< IToolkit > FoundAssetEditor = FToolkitManager::Get().FindEditorForAsset(ParentGraph->GetOuter());
	//Assert cause you cant create comment if your editor isnt opened
	if (!FoundAssetEditor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Asset Editor isnt found") );
		return CommentNode;
	}
	FQuestSystemBaseEditor* QuestEditor = static_cast<FQuestSystemBaseEditor*>(FoundAssetEditor.Get());

	FSlateRect Bounds;
	FVector2D SpawnLocation;
	if (QuestEditor->GetGraphEditor()->GetBoundsForSelectedNodes(Bounds, 50.f))
	{
		CommentNode->SetBounds(Bounds);
		SpawnLocation.X = CommentNode->NodePosX;
		SpawnLocation.Y = CommentNode->NodePosY;
	}
	return FEdGraphSchemaAction_NewNode::SpawnNodeFromTemplate<UEdGraphNode_Comment>(ParentGraph,CommentNode,SpawnLocation,bSelectNewNode);
}


FAddNodeContextAction::FAddNodeContextAction(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, const int32 InGrouping, TSubclassOf<UEdGraphNode> Node)
	: FEdGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping) {
	NodeClass = Node;
}

FBPExecutorContextAction::FBPExecutorContextAction(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, const int32 InGrouping)
	: FAddNodeContextAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping, UEventExecutorNode::StaticClass())
{}

FObjectiveContextAction::FObjectiveContextAction(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, const int32 InGrouping)
	: FAddNodeContextAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping, UQuestObjectiveNode::StaticClass()) {}

FScriptableObjectContextAction::FScriptableObjectContextAction(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, const int32 InGrouping)
	: FAddNodeContextAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping, UScriptableNode::StaticClass()) {}

FQuestEdGraphAction_AddComment::FQuestEdGraphAction_AddComment() 
	: FAddNodeContextAction(FText::FromString("Comment"), FText::FromString("Create Comment"), FText::FromString("Comment"), 0, UEdGraphNode_Comment::StaticClass()) {}