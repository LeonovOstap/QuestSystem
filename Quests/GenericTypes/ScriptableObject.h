// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Quests/Misc/Interfaces/QuestBaseInterfaces.h"
#include "UObject/NoExportTypes.h"
#include "ScriptableObject.generated.h"

/**
 * 
 */


UCLASS()
class QUESTS_API AScriptableObject : public AActor, public IQuestBaseInterface
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActivationDelegate);
	GENERATED_BODY()
		public:
			UFUNCTION(BlueprintCallable,Category="Quests|Scriptable Objects")
				virtual void ActivateObject();
			UFUNCTION(BlueprintCallable,Category="Quests|Scriptable Objects")
				virtual void SendCompletionCallback();
			UFUNCTION(BlueprintNativeEvent,Category="Quests|Scriptable Objects")
				void OnActivation();
				virtual void Start() override;
                
                virtual void Big() {
                UE_LOG(LogTemp,Log,TEXT("%s"),*GetName())};
				virtual FQuestLocalization GetLocalizationInfo() override { return LocaleStruct; };

		public:
			UPROPERTY(EditAnywhere, BlueprintReadOnly)
				FQuestLocalization LocaleStruct;
			FActivationDelegate ActivationDelegate;
			virtual bool GetIsActive() const override {return isActive;};
			virtual void SetActive(bool bIsActive) override{isActive=bIsActive;};
		private:
			UPROPERTY()
				bool isActive;
};

UCLASS()
class QUESTS_API ACallbackOnlyScriptableObject : public AScriptableObject
{
	GENERATED_BODY()
		public:
			ACallbackOnlyScriptableObject();

			UFUNCTION(BlueprintImplementableEvent, Category = "Quests|Scriptable Objects")
				void ReceiveCallback();
		private:
			void ActivateObject() override {};
};