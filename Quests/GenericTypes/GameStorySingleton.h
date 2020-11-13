// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Quests/Misc/Interfaces/BlueprintScriptHolderInterface.h"
#include "Quest.h"
#include "Quests/Misc/Interfaces/QuestBaseInterfaces.h"
#include "UObject/NoExportTypes.h"
#include "GameStorySingleton.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class QUESTS_API UGameStorySingleton : public UQuestBase
{
	GENERATED_BODY()
	protected:
		//IBlueprintScriptHolder
		virtual TSubclassOf<UQuestBlueprintBaseTemplate> GetScriptTemplate() override {return UQuestBlueprintBaseTemplate::StaticClass();};
		//Base Method
		void PostLoad() override;
	
};
