// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintScriptHolderInterface.h"
//#include "Kismet2/KismetEditorUtilities.h"


TSubclassOf<UQuestBlueprintBaseTemplate> IBlueprintScriptHolder::GetScriptTemplate()
{
	return UQuestBlueprintBaseTemplate::StaticClass();
}

UQuestBlueprintBaseTemplate* IBlueprintScriptHolder::GetScriptObject()
{
	return (UQuestBlueprintBaseTemplate*)(FindObjectWithOuter(_getUObject(),UQuestBlueprintBaseTemplate::StaticClass()));
}


