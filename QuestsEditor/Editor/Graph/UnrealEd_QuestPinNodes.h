// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EdGraph/EdGraphNode.h"
#include "CoreMinimal.h"
#include "Quests/Graph/Nodes/RuleNodeFunctions.h"
#include "Quests/Nodes/GraphNodeImplementations.h"
#include "Quests/GenericTypes/ScriptableObject.h"
#include "UnrealEd_QuestPinNodes.generated.h"

/**
 * 
 */
/*Base Node*/
UCLASS()
class QUESTSEDITOR_API UQuestBaseNode : public UEdGraphNode
{
	GENERATED_BODY()
		public:
		UQuestBaseNode();
		UPROPERTY()
			TScriptInterface<IQuestBaseInterface> Owner;
			virtual IQuestBaseInterface* GetOwner();
			virtual TSubclassOf<UPackagedNodeData> PackagingClass() { return UPackagedNodeData::StaticClass(); };
			virtual void AllocateDefaultPins() override;
			virtual UEdGraphPin* CreateNodePin(EEdGraphPinDirection Direction,FName Name);
			virtual bool SupportsCommentBubble() { return true; }
		protected:
			UEdGraphPin* FindPin_Packaging(FName Name,EEdGraphPinDirection Direction);

};
/*Start End Nodes*/
UCLASS()
class QUESTSEDITOR_API UQuestStartNode : public UQuestBaseNode
{
	GENERATED_BODY()
		public:
			virtual void AllocateDefaultPins() override;
			virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
			virtual FText GetTooltipText() const override;
			virtual TSubclassOf<UPackagedNodeData> PackagingClass() { return UPackagedStartNode::StaticClass(); };
};
UCLASS()
class QUESTSEDITOR_API UQuestEndNode : public UQuestBaseNode
{
	
	GENERATED_BODY()
		public:
			virtual void AllocateDefaultPins() override;
			virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
			virtual FText GetTooltipText() const override;
			virtual TSubclassOf<UPackagedNodeData> PackagingClass() { return UPackagedEndNode::StaticClass(); };
};

/*Objective Node(Used in quest graph)*/
UCLASS()
class QUESTSEDITOR_API UQuestObjectiveNode : public UQuestBaseNode
{
	GENERATED_BODY()
		public:
			UQuestObjectiveNode();
			virtual void AllocateDefaultPins() override;
			virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
			virtual FText GetTooltipText() const override;

			virtual FLinearColor GetNodeBodyTintColor() const override;
			virtual FLinearColor GetNodeTitleColor() const override { return GetNodeBodyTintColor(); };
			virtual TSubclassOf<UPackagedNodeData> PackagingClass() { return UPackagedQuestNode::StaticClass(); };
			//void CompleteObjective();
			
};

/*Rule Node*/
UCLASS()
class QUESTSEDITOR_API URuleNode : public UQuestBaseNode
{
	GENERATED_BODY()
		public:
			virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override {return FText::FromString(NodeImplementation.GetDefaultObject()->NodeName);};
			virtual FLinearColor GetNodeBodyTintColor() const override {
				return NodeImplementation.GetDefaultObject()->NodeColor;
			};
			virtual FLinearColor GetNodeTitleColor() const override { return GetNodeBodyTintColor(); };
			virtual void AllocateDefaultPins() override;
			virtual TSubclassOf<UPackagedNodeData> PackagingClass() { return UPackagedRuleNode::StaticClass(); };
			UPROPERTY(EditDefaultsOnly, meta = (Packaged=true))
				TSubclassOf<URuleNodeImplementation> NodeImplementation = URuleNodeImplementation::StaticClass();
			UPROPERTY()
				URuleNodeImplementation* Rule;
};
/*Script Node*/
UCLASS()
class QUESTSEDITOR_API UScriptableNode : public UQuestBaseNode
{
	GENERATED_BODY()
		public:
			UScriptableNode();
			UPROPERTY(meta=(Packaged=true))
				TSoftObjectPtr<AScriptableObject> ScriptableObject;
			virtual IQuestBaseInterface* GetOwner() override {return ScriptableObject.Get();};
			virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override {return FText::FromString(FString("Reference Scriptable Object (").Append(ScriptableObject.Get()->GetName()).Append(")").Append(" "));};
			virtual FLinearColor GetNodeBodyTintColor() const override {return ScriptableObject.Get()->IsA(ACallbackOnlyScriptableObject::StaticClass()) ?
				FLinearColor::Red : FLinearColor::FromSRGBColor(FColor::FromHex("#34c3eb"));};
			virtual FLinearColor GetNodeTitleColor() const override { return GetNodeBodyTintColor(); };
			virtual void AllocateDefaultPins() override;
			virtual TSubclassOf<UPackagedNodeData> PackagingClass() { return UPackagedScriptNode::StaticClass(); };

};


UCLASS()
class QUESTSEDITOR_API UEventExecutorNode : public UQuestBaseNode
{
	GENERATED_BODY()
		public:
			UPROPERTY(EditAnywhere)
				TMap<FName, bool> Functions;
			void ReloadFunctions();
			virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override {
				return FText::FromString(FString("Execute Events from Blueprint"));
			}
			virtual FLinearColor GetNodeBodyTintColor() const override {
				return FLinearColor::FromSRGBColor(FColor::FromHex("#00a4eb"));
			}
			virtual FLinearColor GetNodeTitleColor() const override { return GetNodeBodyTintColor(); };
			virtual void AllocateDefaultPins() override;

};