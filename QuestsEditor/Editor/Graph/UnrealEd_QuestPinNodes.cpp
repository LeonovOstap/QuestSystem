// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealEd_QuestPinNodes.h"
#include "UnrealEd_QuestGraph.h"
#include "EdGraph/EdGraphPin.h"
#include "Engine/Engine.h"
#include "Quests/GenericTypes/Objective.h"

UQuestBaseNode::UQuestBaseNode()
{

}

IQuestBaseInterface* UQuestBaseNode::GetOwner()
{
	return Cast<IQuestBaseInterface>(Owner.GetObject());
}


/*Base Node*/



void UQuestBaseNode::AllocateDefaultPins()
{
	CreateNodePin(EGPD_Input,FName());
	CreateNodePin(EGPD_Output,FName());
	
	//GetOwner()->GetNodeData()->AddInputPin(0,FString("IQuestBaseInterface::Start"),GetOwner()->_getUObject());
	//GetOwner()->GetNodeData()->AddInputPin(1,FString("IQuestBaseInterface::End"),GetOwner()->_getUObject());
}

UEdGraphPin* UQuestBaseNode::CreateNodePin(EEdGraphPinDirection Direction, FName Name)
{
	UEdGraphPin* CreatedPin = CreatePin(Direction,FName(),Name);
	CreatedPin->DefaultObject = NewObject<UPackagedPin>();
	return CreatedPin;
}


UEdGraphPin* UQuestBaseNode::FindPin_Packaging(FName Name,EEdGraphPinDirection Direction)
{
	#if WITH_EDITORONLY_DATA
		return FindPin(Name,Direction);
	#endif

	for(UEdGraphPin* Pin : Pins)
	{
		if(Pin->Direction == Direction && Pin->PinName == Name)
			return Pin;
	}
	return nullptr;
}

/*Start Node*/
void UQuestStartNode::AllocateDefaultPins()
{
	CreateNodePin(EGPD_Output, NAME_None);
}

FText UQuestStartNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString("Start Node");
}

FText UQuestStartNode::GetTooltipText() const
{
	return FText();
}



/*End Node*/
void UQuestEndNode::AllocateDefaultPins()
{
	CreateNodePin(EGPD_Input,FName());
	
	//GetOwner()->GetNodeData()->AddInputPin(0,FString("IQuestBaseInterface::End"),GetOwner()->_getUObject());
}

FText UQuestEndNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString("End Node");
}
FText UQuestEndNode::GetTooltipText() const
{
	return FText();
}

/*Objective Node*/

UQuestObjectiveNode::UQuestObjectiveNode()
{
}

void UQuestObjectiveNode::AllocateDefaultPins()
{	
	Super::AllocateDefaultPins();

}
FText UQuestObjectiveNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(((UObjective*)Owner.GetObject())->GetName());
}
FText UQuestObjectiveNode::GetTooltipText() const
{
	return FText();
}

FLinearColor UQuestObjectiveNode::GetNodeBodyTintColor() const
{
	return FLinearColor(FColor::FromHex("#3AF562"));
}

/*Rule Node*/

	/*if(!Rule) Rule = NewObject<URuleNodeImplementation>(this,NodeImplementation);

	TScriptInterface<IQuestBaseInterface> ActivatedPin = TScriptInterface<IQuestBaseInterface>(Cast<UQuestBaseNode>(On->LinkedTo[0]->GetOwningNode())->GetOwner()->_getUObject());

	TArray<TScriptInterface<IQuestBaseInterface>> AllPins;
	for (UEdGraphPin* Pin : Pins)
	{
		if (Pin->LinkedTo.Num() >= 1 && Pin->Direction == EGPD_Input)
		{
			TScriptInterface<IQuestBaseInterface> Interface = TScriptInterface<IQuestBaseInterface>(Cast<UQuestBaseNode>(Pin->LinkedTo[0]->GetOwningNode())->GetOwner()->_getUObject());
			AllPins.AddUnique(Interface);
			
		}
	}


	bool canEnter = Rule->CanEnter(ActivatedPin, AllPins);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::FromInt(canEnter));

	if (canEnter)
	{
		SendActivation(FindPin_Packaging(FName("Out"), EGPD_Output));
		Rule->ConditionalBeginDestroy();
		Rule = nullptr;
	}*/

void URuleNode::AllocateDefaultPins()
{
	CreateNodePin(EGPD_Output, FName("Out"));
	
	CreateNodePin(EGPD_Input, FName("1"));
	CreateNodePin(EGPD_Input, FName("2"));
	CreateNodePin(EGPD_Input, FName("3"));
	CreateNodePin(EGPD_Input, FName("4"));
	CreateNodePin(EGPD_Input, FName("5"));
}

UScriptableNode::UScriptableNode()
{
	//Owner = ScriptableObject.Get();
}


/*Script Node*/

		//AScriptableObject* Instance = ScriptableObject.Get();
	
		//If Quest design sucks, crash the game
		//check(Instance);

		//Instance->ActivateObject();


void UScriptableNode::AllocateDefaultPins()
{
	CreateNodePin(EGPD_Output, FName(""));
	
	CreateNodePin(EGPD_Input, FName(""));
}


/*Event Executor Node*/

void UEventExecutorNode::AllocateDefaultPins()
{
	CreateNodePin(EGPD_Output, FName(""));

	CreateNodePin(EGPD_Input, FName(""));
}

void UEventExecutorNode::ReloadFunctions()
{
	//for (TFieldIterator<UFunction> It(Cast<IBlueprintScriptHolder>(GetOuter()->GetOuter())->GeneratedScriptClass, EFieldIteratorFlags::ExcludeSuper); It; ++It)
	//{
		//Functions.Emplace(It->GetFName(), false);
	//}
}



	/*IBlueprintScriptHolder* ScriptHolder = Cast<IBlueprintScriptHolder>(GetOuter()->GetOuter());

	if (!ScriptHolder) return;

	for (auto& Elem : Functions)
	{
		if (Elem.Value)
		{
			ScriptHolder->GetScriptObject()->ProcessEvent(ScriptHolder->GetScriptObject()->FindFunction(Elem.Key),nullptr);
		}
	}

	SendActivation(FindPin_Packaging(FName(""), EGPD_Output));*/
