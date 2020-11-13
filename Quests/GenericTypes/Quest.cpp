// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest.h"

#include "UObjectIterator.h"
#include "Engine/Engine.h"




void UQuest::Start()
{
    //Call Super
  // IQuestBaseInterface::Start();
   Super::Start();

    for(TObjectIterator<UQuestBlueprintBaseTemplate> It;It;++It)
        UE_LOG(LogTemp,Log,TEXT("Nama - %s"),*It->GetName());
    
   if((UQuestBlueprintBaseTemplate*)(FindObjectWithOuter(_getUObject(),UQuestBlueprintBaseTemplate::StaticClass())))
       ((UQuestBlueprintBaseTemplate*)(FindObjectWithOuter(_getUObject(),UQuestBlueprintBaseTemplate::StaticClass())))->OnActivation();
    else
        GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Red,"Bitch RETARDED");
   GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Red,"Quest Started");
}

void UQuest::PostLoad()
{
	Super::PostLoad();
}

void UQuest::End()
{
    //Call Super
    IQuestBaseInterface::End();
	if(GetScriptObject()) GetScriptObject()->OnCompletion();
    GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Red,"Quest Ended");
}



