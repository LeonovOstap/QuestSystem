// Fill out your copyright notice in the Description page of Project Settings.


#include "ScriptableObject.h"


void AScriptableObject::ActivateObject()
{
	Start();
}

void AScriptableObject::SendCompletionCallback()
{
	End();
}

void AScriptableObject::Start()
{
	IQuestBaseInterface::Start();
	OnActivation_Implementation();
}

void AScriptableObject::OnActivation_Implementation()
{
}


ACallbackOnlyScriptableObject::ACallbackOnlyScriptableObject()
{
	SetActive(true);
}

