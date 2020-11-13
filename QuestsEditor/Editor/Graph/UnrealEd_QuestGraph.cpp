// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealEd_QuestGraph.h"
#include "Delegates/DelegateBase.h"



/*Base Node*/
void UnrealEd_BaseQuestGraph::ActivateStartNode()
{
	TArray<UQuestStartNode*> StartNodes;
	GetNodesOfClass<UQuestStartNode>(StartNodes);

//	StartNodes[0]->ReceiveActivation(nullptr);
	//ExecutionGraph->GetNodeByName(StartNodes[0]->GetFName())->ReceiveActivation(ExecutionGraph->GetNodeByName(StartNodes[0]->GetFName())->FindPin(0));
}

void UnrealEd_BaseQuestGraph::FinishEvent()
{
	//IQuestBaseInterface* i = Cast<IQuestBaseInterface>(GetOuter());
	//if(i)
	//	i->End();
}
void UnrealEd_BaseQuestGraph::SendCallbackToAssociatedNode(UObject * ParamToLookFor)
{
}
/*Objective Node*/

