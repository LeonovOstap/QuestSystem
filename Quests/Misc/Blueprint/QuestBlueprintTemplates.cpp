// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestBlueprintTemplates.h"
#include "Quests/GenericTypes/Quest.h"
#include "Quests/GenericTypes/Objective.h"


/*Objective Template*/
UObjective* UObjectiveBlueprintTemplate::GetObjective()
{
	return Cast<UObjective>(GetOuter());
}

/*Quest Template*/
UQuest* UQuestBlueprintTemplate::GetQuest()
{
	return Cast<UQuest>(GetOuter());
}