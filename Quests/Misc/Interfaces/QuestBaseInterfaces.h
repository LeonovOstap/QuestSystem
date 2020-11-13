// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActivatableInterface.h"
#include "UObjectHash.h"
#include "QuestBaseInterfaces.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FQuestLocalization
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText LocalizedName = FText();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText LocalizedDesciprion = FText();
};

UINTERFACE()
class QUESTS_API UQuestBaseInterface : public UActivatableInterface
{
	GENERATED_BODY()
};


class QUESTS_API IQuestBaseInterface : public IActivatableInterface
{
    GENERATED_BODY()
 public:

		virtual FQuestLocalization GetLocalizationInfo() { return FQuestLocalization(); };
		UFUNCTION()
		   virtual void Start();
		UFUNCTION()
			virtual void End();

	//	virtual FPackagedNodeData* GetNodeData(){return nullptr;};

};
