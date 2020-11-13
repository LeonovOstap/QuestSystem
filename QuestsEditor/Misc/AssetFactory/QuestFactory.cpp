// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestFactory.h"

#include "Quests/GenericTypes/GameStorySingleton.h"
#include "Quests/GenericTypes/Quest.h"
#include "Quests/GenericTypes/Objective.h"

UQuestFactory::UQuestFactory()
{
	SupportedClass = UQuest::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}


UObject* UQuestFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UQuest* Quest = NewObject<UQuest>(InParent, Class, Name, Flags | RF_Transactional);
	return Quest;
}

UObjectiveFactory::UObjectiveFactory()
{
	SupportedClass = UObjective::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject * UObjectiveFactory::FactoryCreateNew(UClass * Class, UObject * InParent, FName Name, EObjectFlags Flags, UObject * Context, FFeedbackContext * Warn)
{
	return NewObject<UObjective>(InParent, Class, Name, Flags | RF_Transactional);
}

UObject* UStorySingletonFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UGameStorySingleton>(InParent, InClass, InName, Flags | RF_Transactional);
}

UStorySingletonFactory::UStorySingletonFactory()
{
	SupportedClass = UGameStorySingleton::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

