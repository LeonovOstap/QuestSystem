// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphNodeImplementations.h"

#include "EngineUtils.h"


void UPackagedStartNode::ReceiveActivation(UPackagedPin* OnPin)
{
	SendActivation(Pins[0]);
}

void UPackagedEndNode::ReceiveActivation(UPackagedPin* OnPin)
{
	GetGraph()->GetOwner()->End();
}

void UPackagedQuestNode::ReceiveActivation(UPackagedPin* OnPin)
{
	if (OnPin->PinDirection == EGPD_Input)
	{
		GetNodeOwner()->Start();
	}
}

void UPackagedScriptNode::ReceiveActivation(UPackagedPin* OnPin)
{
	if(OnPin->PinDirection == EGPD_Input)
	{
		if(ScriptableObject.IsValid())
				ScriptableObject->Start();
	}
}

void UPackagedRuleNode::ReceiveActivation(UPackagedPin* OnPin)
{
	if(!Rule) Rule = NewObject<URuleNodeImplementation>(this,NodeImplementation);

    //UE_LOG(LogTemp, Log, TEXT("Rule class name %s"), *Rule->GetClass()->GetName());
	TScriptInterface<IQuestBaseInterface> ActivatedPin = OnPin->GetOwningNode()->NodeOwner? TScriptInterface<IQuestBaseInterface>(OnPin->GetOwningNode()->GetNodeOwner()->_getUObject()) : TScriptInterface<IQuestBaseInterface>();

	TArray<TScriptInterface<IQuestBaseInterface>> AllPins;
	for (UPackagedPin* Pin : Pins)
	{
		if (Pin->LinkedTo.Num() >= 1 && Pin->PinDirection == EGPD_Input)
		{
			TScriptInterface<IQuestBaseInterface> Interface = Pin->GetOwningNode()->NodeOwner? TScriptInterface<IQuestBaseInterface>(Pin->GetOwningNode()->GetNodeOwner()->_getUObject()) : TScriptInterface<IQuestBaseInterface>();
			AllPins.AddUnique(Interface);			
		}
	}


	bool canEnter = Rule->CanEnter(ActivatedPin, AllPins);

	if (canEnter)
	{
		EndNode();
		Rule->ConditionalBeginDestroy();
		Rule = nullptr;
	}
}

void UPackagedEventExecutorNode::ReceiveActivation(UPackagedPin* OnPin)
{
}
