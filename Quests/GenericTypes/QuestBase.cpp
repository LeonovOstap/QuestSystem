// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestBase.h"
#include "Quests/Nodes/GraphNodeImplementations.h"
#include "Engine/Engine.h"

UQuestBase::UQuestBase()
{
    ExecutionGraph = CreateDefaultSubobject<UExecutionGraph>(*GetName().Append("_ExecutionGraph"));
}

void UQuestBase::Start()
{
    IQuestBaseInterface::Start();
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "ActivatingNode");
	ExecutionGraph->GetFirstNodeByClass(UPackagedStartNode::StaticClass())->StartNode();
	
}

void UQuestBase::Tick(float DeltaTime)
{
	BlueprintBaseTemplate->EventTick(DeltaTime);
}

bool UQuestBase::IsTickable() const
{
	if(!bTickable) return false;
	return bAlwaysTick || isActive;
}
