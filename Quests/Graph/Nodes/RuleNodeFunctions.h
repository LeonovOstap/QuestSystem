// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RuleNodeFunctions.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI,Blueprintable,HideDropdown)
class URuleNodeImplementation : public UObject
{
	GENERATED_BODY()
	public:
		UFUNCTION(BlueprintNativeEvent)
		bool CanEnter(const TScriptInterface <IQuestBaseInterface>& ActivatedPin,const TArray<TScriptInterface<IQuestBaseInterface>>& AllPins);

		UPROPERTY(EditDefaultsOnly)
			FLinearColor NodeColor = FLinearColor::Red;
		UPROPERTY(EditDefaultsOnly)
			FString NodeName = "Rule Node";

};
