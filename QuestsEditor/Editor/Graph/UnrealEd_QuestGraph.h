// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnrealEd_QuestPinNodes.h"
#include "EdGraph/EdGraph.h"
#include "UnrealEd_QuestGraph.generated.h"

/**
 * 
 */
UCLASS()
class QUESTSEDITOR_API UnrealEd_BaseQuestGraph : public UEdGraph
{
	GENERATED_BODY()
	public:
			/*Activates Start Node In Graph*/
			virtual void ActivateStartNode();
			/*Called by end Node used to end t*/
			virtual void FinishEvent();
			/*Called when node Receives signal*/
			virtual void SendCallbackToAssociatedNode(UObject * ParamToLookFor);
};
 
UCLASS()
class QUESTSEDITOR_API UnrealEd_QuestGraph : public UnrealEd_BaseQuestGraph
{
	GENERATED_BODY()
};

UCLASS()
class QUESTSEDITOR_API UnrealEd_ObjectiveGraph : public UnrealEd_BaseQuestGraph
{
	GENERATED_BODY()
};