// Fill out your copyright notice in the Description page of Project Settings.


#include "Objective.h"
#include "Engine/Engine.h"

UObjective::UObjective()
{
}

void UObjective::End()
{
    IQuestBaseInterface::End();

	if(GetScriptObject()) GetScriptObject()->OnCompletion();
    GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Red,"Objective Completed");
}


void UObjective::PostLoad()
{
	Super::PostLoad();
}


void UObjective::Start()
{
    Super::Start();
	UQuestBlueprintBaseTemplate* Obj = FindObject<UQuestBlueprintBaseTemplate>(this,*GetName().Append("_Script"));

	if(Obj)
		Obj->OnActivation();
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Objective Activated");
}


