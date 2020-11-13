// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeDataPackaged.h"

#include "UObjectIterator.h"

UPackagedNodeData* UExecutionGraph::GetNodeByName(FName Name)
{
    for(auto Node : NodeDatas)
    {
        if(Node->NodeName == Name)
            return Node;
    }
    return nullptr;
}

UPackagedNodeData * UExecutionGraph::GetFirstNodeByClass(TSubclassOf<UPackagedNodeData> NodeClass)
{
	for (auto Node : NodeDatas)
	{
		if (Node->IsA(NodeClass))
			return Node;
	}
	return nullptr;
}

UPackagedNodeData* UExecutionGraph::GetNodeByOwner(IQuestBaseInterface* Owner)
{
	for(TObjectIterator<UPackagedNodeData> It;It;++It)
	{
		if(It->GetNodeOwner() == Owner)
			return *It;
	}
	return nullptr;
}

UPackagedNodeData::UPackagedNodeData()
{
}


void UPackagedNodeData::EndNode()
{
	auto Pin = *(Pins.FindByPredicate([](UPackagedPin* Pin){return Pin->PinDirection == EGPD_Output;}));
	if(Pin)
		SendActivation(Pin);
}

void UPackagedNodeData::SendActivation(UPackagedPin* FromPin)
{
    for(auto LinkedPin : FromPin->LinkedTo)
    {
        LinkedPin->GetOwningNode()->ReceiveActivation(LinkedPin);
    }
}

void UPackagedNodeData::ReceiveActivation(UPackagedPin* OnPin)
{

    
}

UPackagedPin* UPackagedNodeData::FindPin(int Index)
{
    for(auto Pin : Pins)
    {
        if(Pin->PinIndex == Index)
            return Pin;
    }
    
    return nullptr;
}

UPackagedPin * UPackagedNodeData::FindPin(FName Name)
{
	for (auto Pin : Pins)
	{
		if (Pin->PinName == Name)
			return Pin;
	}
	return nullptr;
}

UPackagedPin* UPackagedNodeData::FirstPin(EEdGraphPinDirection PinDirection)
{
	for (auto Pin : Pins)
	{
		if (Pin->PinDirection == PinDirection)
			return Pin;
	}
	return nullptr;
}
