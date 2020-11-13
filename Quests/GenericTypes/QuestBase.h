// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/Interfaces/BlueprintScriptHolderInterface.h"
#include "Misc/Interfaces/QuestBaseInterfaces.h"
#include "UObject/NoExportTypes.h"
#include "EdGraph/EdGraph.h"
#include "QuestBase.generated.h"



/**
 * 
 */
class UExecutionGraph;

UCLASS()
class QUESTS_API UQuestBase : public UObject, public IQuestBaseInterface,public IBlueprintScriptHolder,public FTickableGameObject
{
	GENERATED_BODY()
		public:
			UQuestBase();
			UPROPERTY()
				UExecutionGraph* ExecutionGraph;
			UPROPERTY()
				UQuestBlueprintBaseTemplate* BlueprintBaseTemplate;

			//Activatable Interface
			virtual void SetActive(bool bIsActive) override {isActive = bIsActive;};
			virtual bool GetIsActive() const override {return isActive;};


			UPROPERTY()
				bool isActive = false;
		public:
			virtual void Start() override;
			
			#if WITH_EDITORONLY_DATA
			UPROPERTY()
				UEdGraph* QuestGraph;
			#endif
		private:
			//FTickableGameObject Interface
			virtual bool IsTickableInEditor() const override {return false;};
			virtual bool IsTickableWhenPaused() const override {return false;};
			virtual void Tick(float DeltaTime) override;
			virtual bool IsTickable() const override;
			virtual UWorld* GetTickableGameObjectWorld() const override {return GWorld;};
			virtual ETickableTickType GetTickableTickType() const override {return ETickableTickType::Conditional;};
			virtual TStatId GetStatId() const override {return TStatId();};
			//End FTickableGameObject Interface

			//Will dump performance drastically if used recklessly, Nativization is strongly advised
			UPROPERTY(EditDefaultsOnly,meta=(AllowPrivateAccess=true))
				bool bTickable = false;
			//Use only if you really need to (Script will tick always when Object is loaded(whole game))
			UPROPERTY(EditDefaultsOnly,meta=(AllowPrivateAccess=true))
				bool bAlwaysTick = false;
};
