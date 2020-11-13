// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestBaseInterfaces.h"

#include "Nodes/NodeDataPackaged.h"


void IQuestBaseInterface::Start()
{
    if(GetIsActive())
    {
       // UE_LOG(LogTemp, Warning, TEXT("Quest %s seems to be already active,du-activation will be ignored"),*((UObject*)this)->GetName());
        return;
    }
    SetActive(true);
}

void IQuestBaseInterface::End()
{
    if(!GetIsActive())
    {
        //UE_LOG(LogTemp, Warning, TEXT("Quest %s is not active,deactivation will be ignored"),*((UObject*)this)->GetName());
        return;
    }
    auto Node = UExecutionGraph::GetNodeByOwner(this);
    if(Node)
        Node->EndNode();
    SetActive(false);
}

