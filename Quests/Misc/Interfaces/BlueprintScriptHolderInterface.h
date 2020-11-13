// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UObjectHash.h"
#include "UObject/NoExportTypes.h"
#include "Quests/Misc/Blueprint/QuestBlueprintTemplates.h"
#include "BlueprintScriptHolderInterface.generated.h"

/**
 * 
 */
UINTERFACE()
class QUESTS_API UBlueprintScriptHolder : public UInterface
{
	GENERATED_BODY()
};

class QUESTS_API IBlueprintScriptHolder
{
	GENERATED_BODY()
	public:
		virtual TSubclassOf<UQuestBlueprintBaseTemplate> GetScriptTemplate();
		UQuestBlueprintBaseTemplate* GetScriptObject();

};