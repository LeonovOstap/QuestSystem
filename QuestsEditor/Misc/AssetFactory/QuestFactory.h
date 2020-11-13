// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "QuestFactory.generated.h"

/**
 * 
 */
UCLASS()
class QUESTSEDITOR_API UQuestFactory : public UFactory
{
	GENERATED_BODY()
	public:
		UQuestFactory();
		virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	
};
UCLASS()
class QUESTSEDITOR_API UObjectiveFactory : public UFactory
{
	GENERATED_BODY()
		public:
			UObjectiveFactory();
			virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};

UCLASS()
class QUESTSEDITOR_API UStorySingletonFactory : public UFactory
{
	GENERATED_BODY()
	public:
		UStorySingletonFactory();
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};