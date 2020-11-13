// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objective.h"
#include "QuestBase.h"
#include "Quest.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class QUESTS_API UQuest : public UQuestBase
{
	GENERATED_BODY()
	
	
	public:
		FQuestLocalization GetLocalizationInfo() override { return LocaleStruct; };

		UFUNCTION(BlueprintCallable)
		void StartQuest() {Start();};

		/*Quest Base Interface*/
		void End() override;
		void Start() override;
	public:
		UPROPERTY(EditAnywhere, BlueprintReadOnly)
			FQuestLocalization LocaleStruct;
	protected:
		/*Blueprint Script holder*/
		void PostLoad() override;
		virtual TSubclassOf<UQuestBlueprintBaseTemplate> GetScriptTemplate() override { return UQuestBlueprintTemplate::StaticClass(); };

};
