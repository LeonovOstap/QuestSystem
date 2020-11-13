// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintScriptManager.h"


#include "AssetEditorManager.h"
#include "BlueprintNodeHelpers.h"
#include "KismetEditorUtilities.h"

void FBlueprintScriptManager::OpenBlueprintForObject(UQuestBase* QuestBase)
{     
    FAssetEditorManager::Get().OpenEditorForAsset(FindBlueprint(QuestBase));
}

UBlueprint* FBlueprintScriptManager::FindBlueprint(UQuestBase* QuestBase)
{
    auto Bp = (UBlueprint*)(FindObjectWithOuter(QuestBase,UBlueprint::StaticClass()));
    return Bp? Bp : CreateBlueprint(QuestBase);
}

UBlueprint* FBlueprintScriptManager::CreateBlueprint(UQuestBase* QuestBase)
{
    UBlueprint* Blueprint =  FKismetEditorUtilities::CreateBlueprint(QuestBase->GetScriptTemplate(),
        QuestBase,
        FName(*QuestBase->GetName().Append("_BP")),
        EBlueprintType::BPTYPE_Normal,
        UBlueprint::StaticClass(),
        UBlueprintGeneratedClass::StaticClass());
    Blueprint->OnCompiled().AddStatic(&FBlueprintScriptManager::OnRecompile);

    FKismetEditorUtilities::CompileBlueprint(Blueprint);

  //  auto New = NewObject<UQuestBlueprintBaseTemplate>(QuestBase,Blueprint->GeneratedClass,*Blueprint->GetName().Append("_Script"));
   // QuestBase->BlueprintBaseTemplate = New;
    
    return Blueprint;
}

void FBlueprintScriptManager::OnRecompile(UBlueprint* Blueprint)
{
    UQuestBase* Owner = Cast<UQuestBase>(Blueprint->GetOuter());

    check(Owner);
    
    if(auto Object = FindObject<UQuestBlueprintBaseTemplate>(Owner,TEXT("")))
    {
        Object->ConditionalBeginDestroy();
    }

    auto New = NewObject<UQuestBlueprintBaseTemplate>(Owner,Blueprint->GeneratedClass,*Blueprint->GetName().Append("_Script"));
    Owner->BlueprintBaseTemplate = New;
}
