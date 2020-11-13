// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeCompiler.h"
#include "UObjectIterator.h"
#include "Engine/Engine.h"
#include "EdGraph/EdGraphPin.h"
#include "Log/LogUtilities.h"
#include "Dialogs/SOutputLogDialog.h"
#include "GenericTypes/QuestBase.h"


DEFINE_LOG_CATEGORY(LogQuestNodeCompiler);

void FNodeCompiler::LinkPins(UPackagedNodeData* Package)
{  
    for(UPackagedPin* Pin : Package->Pins)
    {
	    for(UEdGraphPin* IPin : FindPinByGuidInNodes(Pin->Guid)->LinkedTo)
	    {
		    Pin->LinkedTo.Add(FindPackagedPinByGuidInNodes(IPin->PinId));
	    }
    }

}

void FNodeCompiler::PackageNode(UPackagedNodeData* PackagedNodeData,UExecutionGraph* Graph)
{
    UE_LOG(LogQuestNodeCompiler, Log, TEXT("Packaging Node %s"),*PackagedNodeData->NodeName.ToString() );
    
    LinkPins(PackagedNodeData);
    
    //Set Receive function
    //Add Node to PackagedGraph
   // Graph->NodeDatas.AddUnique(PackagedNodeData);
}

void FNodeCompiler::PackageGraph(UnrealEd_BaseQuestGraph* Graph)
{
	FNodeCompilerLog Logger = FNodeCompilerLog();

	UE_LOG(LogQuestNodeCompiler, Log, TEXT("______REPACKAGE GRAPH STARTED______"));

	
	PackageGraph_Internal(Graph);


	UE_LOG(LogQuestNodeCompiler, Log, TEXT("______REPACKAGE GRAPH FINISHED______"));
	
	FText OutputLog = FText::FromString(Logger.OutPut);
	SOutputLogDialog::Open(FText::FromString("Node Compiler Results"),
        FText::FromString(Graph->GetOuter()->GetName().Append(" was succesfully packaged")), OutputLog ,FText::GetEmpty());

	GLog->RemoveOutputDevice(&Logger);
}

void FNodeCompiler::PackageGraph_Internal(UnrealEd_BaseQuestGraph* Graph)
{
	UE_LOG(LogQuestNodeCompiler, Log, TEXT("Packaging Graph %s"),*Graph->GetFullName() );
    UExecutionGraph* ExecutionGraph = Cast<UQuestBase>(Graph->GetOuter())->ExecutionGraph;
	ExecutionGraph->GetOwner()->Modify();
	
    for(auto NodeData : ExecutionGraph->NodeDatas)
    {
    	//NodeData->RemoveFromRoot();
		NodeData->MarkPendingKill();
        NodeData->ConditionalBeginDestroy();
    }
    ExecutionGraph->NodeDatas.Empty();
	
	UE_LOG(LogQuestNodeCompiler, Log, TEXT("Node References Invalidated"));

	for (auto Node : Graph->Nodes)
	{
		if (Node->IsA(UQuestBaseNode::StaticClass()))
		{
			if(Node->IsA(UQuestBaseNode::StaticClass()) && Cast<UQuestBaseNode>(Node)->Owner)
				PackageGraph_Internal((UnrealEd_BaseQuestGraph*) FindObjectWithOuter(Cast<UQuestBaseNode>(Node)->Owner->_getUObject(),UnrealEd_BaseQuestGraph::StaticClass()));
			
			CreatePackagedNode(Cast<UQuestBaseNode>(Node),ExecutionGraph);
		}
	}

	UE_LOG(LogQuestNodeCompiler, Log, TEXT("Relinking Pins for Nodes"));
    for(auto Node : ExecutionGraph->NodeDatas)
    {
    	LinkPins(Node);
    }
	UE_LOG(LogQuestNodeCompiler, Log, TEXT("Nodes Relinked"));
	
}

UPackagedNodeData* FNodeCompiler::CreatePackagedNode(UQuestBaseNode* Node,UExecutionGraph* Graph)
{
	UE_LOG(LogQuestNodeCompiler, Log, TEXT("Packaging Node %s"),*Node->GetName() );
	FString NodeName = Node->GetNodeTitle(ENodeTitleType::FullTitle).ToString();
    UPackagedNodeData* NodeData =  NewObject<UPackagedNodeData>(Graph,Node->PackagingClass(), *NodeName.Append(FString("_Packaged")));
	NodeData->NodeOwner = Node->Owner;
	NodeData->NodeName = Node->GetFName();
	TransferProperties(Node, NodeData);

	//NodeData->AddToRoot();
	
	for (UEdGraphPin* Pin : Node->Pins)
		CreatePackagedPin(Pin, NodeData);

	Graph->NodeDatas.AddUnique(NodeData);
	
    return NodeData;
}

UPackagedPin* FNodeCompiler::CreatePackagedPin(UEdGraphPin * Pin, UPackagedNodeData * Node)
{
	FString PinName = Pin->GetFName().ToString();
	PinName = Node->NodeName.ToString().Append("_PPin_").Append(FString::FromInt(Pin->GetOwningNode()->GetPinIndex(Pin)));
	UE_LOG(LogQuestNodeCompiler, Log, TEXT("Packaging Pin %s"),*PinName );
	
	UPackagedPin* Package = NewObject<UPackagedPin>(Node,*PinName);

	Package->PinIndex = Pin->GetOwningNode()->GetPinIndex(Pin);
	Package->PinDirection = Pin->Direction;
	Package->PinName = Pin->GetFName();
	Package->Guid = Pin->PinId;
	//Package->AddToRoot();
	Node->Pins.Add(Package);
	return Package;
}
UPackagedPin* FNodeCompiler::FindPackagedPinByGuidInNodes(FGuid Guid)
{
	for(TObjectIterator<UPackagedPin> It;It;++It)
	{
		if(It->Guid == Guid)
			return *It;
	}
	
	return nullptr;
}UEdGraphPin* FNodeCompiler::FindPinByGuidInNodes(FGuid Guid)
{
	for(TObjectIterator<UQuestBaseNode> It;It;++It)
	{
		for(auto Pin : It->Pins)
			if(Pin->PinId == Guid)
				return Pin;
	}
	
	return nullptr;
}

void FNodeCompiler::TransferProperties(UQuestBaseNode * From, UPackagedNodeData * To)
{
	TArray<UProperty*> EdGraphProperties;
	for(TFieldIterator<UProperty> Kt(From->GetClass());Kt;++Kt)
	{
		if (Kt->GetBoolMetaData("Packaged"))
		{
			EdGraphProperties.Add(*Kt);
		}
	}
	for (TFieldIterator<UProperty> It(To->GetClass()) ; It; ++It)
	{
		if (It->GetBoolMetaData("Packaged"))
		{
			UProperty* BoundProperty = *EdGraphProperties.FindByPredicate([&](const UProperty* Prop) {return It->GetNameCPP() == Prop->GetNameCPP(); });

			if (!BoundProperty)
			{
				UE_LOG(LogQuestNodeCompiler, Error, TEXT("Property %s has flag for packaging,but no matching property found"), *It->GetNameCPP());
				return;
			}
		
			//Prop->se
			void* ToVal = It->ContainerPtrToValuePtr<void*>(To);
			void* FromVal = BoundProperty->ContainerPtrToValuePtr<void*>(From);


			//int sizeOfBlock=*(int*)FromVal+13;

			//FMemory::BigBlockMemcpy(ToVal,&FromVal,sizeof(FromVal));
			//voidcpy()
			BoundProperty->CopyCompleteValue(ToVal,FromVal);
			//*ToVal = FromVal

			
			//It->SetPropertyValue(Haram, BoundProperty->GetPropertyValue(Param));
		}
	}
}
