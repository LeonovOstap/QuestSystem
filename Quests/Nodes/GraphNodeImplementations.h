// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NodeDataPackaged.h"
#include "GenericTypes/ScriptableObject.h"
#include "Graph/Nodes/RuleNodeFunctions.h"
#include "GraphNodeImplementations.generated.h"

/**
 * 
 */
UCLASS()
class QUESTS_API UPackagedStartNode : public UPackagedNodeData
{
	GENERATED_BODY()
		protected:
			virtual void ReceiveActivation(UPackagedPin* OnPin) override;
};

UCLASS()
class QUESTS_API UPackagedEndNode : public UPackagedNodeData
{
	GENERATED_BODY()
		protected:
			virtual void ReceiveActivation(UPackagedPin* OnPin) override;
	
};

UCLASS()
class QUESTS_API UPackagedQuestNode : public UPackagedNodeData
{
	GENERATED_BODY()
		protected:
			virtual void ReceiveActivation(UPackagedPin* OnPin) override;
};

UCLASS()
class QUESTS_API UPackagedScriptNode : public UPackagedNodeData
{
	GENERATED_BODY()
		public:
			UPROPERTY(meta=(Packaged=true))
				TSoftObjectPtr<AScriptableObject> ScriptableObject;
			virtual TScriptInterface<IQuestBaseInterface> GetNodeOwner() override {return ScriptableObject.Get();};
		protected:
			virtual void ReceiveActivation(UPackagedPin* OnPin) override;
};

UCLASS()
class QUESTS_API UPackagedRuleNode : public UPackagedNodeData
{
	GENERATED_BODY()
		protected:
			virtual void ReceiveActivation(UPackagedPin* OnPin) override;
		private:
			UPROPERTY(meta=(Packaged=true))
				TSubclassOf<URuleNodeImplementation> NodeImplementation;
			UPROPERTY()
				URuleNodeImplementation* Rule;
};

UCLASS()
class QUESTS_API UPackagedEventExecutorNode : public UPackagedNodeData
{
	GENERATED_BODY()
		protected:
			virtual void ReceiveActivation(UPackagedPin* OnPin) override;
};