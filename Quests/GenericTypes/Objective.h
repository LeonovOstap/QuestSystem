// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "QuestBase.h"
#include "UObject/NoExportTypes.h"
#include "ScriptableObject.h"
#include "Quests/Misc/Interfaces/BlueprintScriptHolderInterface.h"
#include "Objective.generated.h"

/**
 * 
 */
//class UObjectiveBlueprintTemplate;

UCLASS(Blueprintable, BlueprintType)
class QUESTS_API UObjective : public UQuestBase
{
	GENERATED_BODY()
		public:
			UObjective();
			/*Quest Base Interface*/
			FQuestLocalization GetLocalizationInfo() override { return LocaleStruct; };
			void Start() override;
			void End() override;
		public:
			UPROPERTY(EditAnywhere,BlueprintReadOnly)
				FQuestLocalization LocaleStruct;
		protected:
			/*Blueprint Script Holder Interface*/
			virtual TSubclassOf<UQuestBlueprintBaseTemplate> GetScriptTemplate() override { return UObjectiveBlueprintTemplate::StaticClass(); };
			/*Base Method overrides*/
			virtual void PostLoad() override;

};




	

