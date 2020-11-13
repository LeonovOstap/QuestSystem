// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BillboardComponent.h"
#include "GameFramework/Actor.h"
#include "Quests/GenericTypes/ScriptableObject.h"
#include "QuestAnchor.generated.h"

UCLASS()
class QUESTS_API AQuestAnchor : public AScriptableObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuestAnchor();
	UPROPERTY(VisibleDefaultsOnly)
		UBillboardComponent* BillboardComponent;

	void Tick(float DeltaSeconds) override;
	virtual bool ShouldTickIfViewportsOnly() const override;

public:
	void OnActivation_Implementation() override;

};
