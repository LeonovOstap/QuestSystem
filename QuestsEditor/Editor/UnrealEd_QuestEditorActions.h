// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlowEditor.h"
#include "EdGraphNode_Comment.h"
#include "QuestsEditor/Editor/Graph/UnrealEd_QuestPinNodes.h"
#include "EdGraph/EdGraphSchema.h"
#include "Quests/GenericTypes/Objective.h"
#include "Quests/GenericTypes/ScriptableObject.h"
#include "EdGraph/EdGraph.h"
//#include "UnrealEd_QuestEditorActions.generated.h"

/**
 * 
 */

struct QUESTSEDITOR_API FAddNodeContextAction : public FEdGraphSchemaAction
{
public:
	FAddNodeContextAction(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, const int32 InGrouping, TSubclassOf<UEdGraphNode> Node);
		
	TSubclassOf<UEdGraphNode> NodeClass;
	virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode) override;
};


struct QUESTSEDITOR_API FObjectiveContextAction : public FAddNodeContextAction
{
public:
	FObjectiveContextAction(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, const int32 InGrouping);

	UObjective* NodeTemplate;
	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
};

struct QUESTSEDITOR_API FScriptableObjectContextAction : public FAddNodeContextAction
{
public:
	FScriptableObjectContextAction(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, const int32 InGrouping);
	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
	AActor* Actor;
};

struct QUESTSEDITOR_API FBPExecutorContextAction : public FAddNodeContextAction
{
public:
	FBPExecutorContextAction(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, const int32 InGrouping);

	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
	UFunction* Function;
};

struct QUESTSEDITOR_API FQuestEdGraphAction_AddComment : public FAddNodeContextAction {
public:
	FQuestEdGraphAction_AddComment();
	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode) override;
};
