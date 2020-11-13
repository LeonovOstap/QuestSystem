// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GenericTypes/QuestBase.h"

#include "BlueprintScriptManager.generated.h"

/**
 * 
 */
USTRUCT()
struct QUESTSEDITOR_API FBlueprintScriptManager
{
 GENERATED_BODY()
    public:
        static FBlueprintScriptManager Get() {return FBlueprintScriptManager();};
        void OpenBlueprintForObject(UQuestBase* QuestBase);
    private:
        UBlueprint* FindBlueprint(UQuestBase* QuestBase);
        UBlueprint* CreateBlueprint(UQuestBase* QuestBase);

        static void OnRecompile(UBlueprint* Blueprint);

};
