// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <xkeycheck.h>


#include "Tickable.h"
#include "Engine/World.h"
#include "UObject/NoExportTypes.h"
#include "QuestBlueprintTemplates.generated.h"

/**
 * 
 */

class UObjective;
class UQuest;
class UQuestBase;

UCLASS(MinimalAPI)
class UQuestBlueprintBaseTemplate : public UObject
{
	GENERATED_BODY()
		public:
			virtual UWorld* GetWorld() const override {return GWorld;};

			UFUNCTION(BlueprintImplementableEvent)
				void OnActivation();
			UFUNCTION(BlueprintImplementableEvent)
				void OnCompletion();
			UFUNCTION(BlueprintImplementableEvent,meta=(DisplayName="Tick"))
				void EventTick(float deltaSeconds);
	
	

};
UCLASS(MinimalAPI)
class UObjectiveBlueprintTemplate : public UQuestBlueprintBaseTemplate
{
	GENERATED_BODY()
		public:
			UFUNCTION(BlueprintCallable, BlueprintPure)
				UObjective* GetObjective();
};
UCLASS(MinimalAPI)
class UQuestBlueprintTemplate : public UQuestBlueprintBaseTemplate
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
		UQuest* GetQuest();
};