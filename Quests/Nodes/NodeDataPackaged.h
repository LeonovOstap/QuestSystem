// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "GenericTypes/QuestBase.h"
#include "EdGraph/EdGraphNode.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "NodeDataPackaged.generated.h"

/**
 * 
 */
class UPackagedPin;
class UPackagedNodeData;
UCLASS()
class QUESTS_API UExecutionGraph : public UObject
{
	GENERATED_BODY()
	public:
		UPROPERTY()
			TArray<UPackagedNodeData*> NodeDatas;
		UPackagedNodeData* GetNodeByName(FName Name);
		UPackagedNodeData* GetFirstNodeByClass(TSubclassOf<UPackagedNodeData> NodeClass);
		UQuestBase* GetOwner() { return Cast<UQuestBase>(GetOuter()); };


		static UPackagedNodeData* GetNodeByOwner(IQuestBaseInterface* Owner);
	protected:
		
};

UCLASS()
class QUESTS_API UPackagedNodeData : public UObject
{
	GENERATED_BODY()
	public:
		UPackagedNodeData();
	//Unsafe Call To Expression,use GetNodeOwner()
		UPROPERTY()
			TScriptInterface<IQuestBaseInterface> NodeOwner;
		UPROPERTY()
			TArray<UPackagedPin*> Pins;
		UPROPERTY()
			FName NodeName;
		void StartNode() { ReceiveActivation(FindPin(0)); };
		void EndNode();
		virtual TScriptInterface<IQuestBaseInterface> GetNodeOwner() {return NodeOwner;};

	protected:
		void SendActivation(UPackagedPin* FromPin);
		virtual void ReceiveActivation(UPackagedPin* OnPin);

		UExecutionGraph* GetGraph() { return Cast<UExecutionGraph>(GetOuter()); };

		UPackagedPin* FindPin(int Index);
		UPackagedPin* FindPin(FName Name);
		UPackagedPin* FirstPin(EEdGraphPinDirection PinDirection);
	private:
		virtual bool CanBeClusterRoot() const override {return true;};
		
};
UCLASS()
class QUESTS_API UPackagedPin : public UObject
{
	GENERATED_BODY()
		public:
			UPROPERTY()
				TArray<UPackagedPin*> LinkedTo;
			UPROPERTY()
				FName PinName;
			UPROPERTY()
				int PinIndex;
			UPROPERTY()
				TEnumAsByte<EEdGraphPinDirection> PinDirection;
			
			UPackagedNodeData* GetOwningNode(){return Cast<UPackagedNodeData>(GetOuter());};
			FGuid Guid;
		private:
			virtual bool CanBeInCluster() const override {return true;};
};
