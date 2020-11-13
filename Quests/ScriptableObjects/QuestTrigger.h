// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Components/BillboardComponent.h"
#include "Quests/GenericTypes/ScriptableObject.h"
#include "QuestTrigger.generated.h"

UCLASS()
class QUESTS_API AQuestTrigger : public ACallbackOnlyScriptableObject
{
	GENERATED_BODY()
	
public:	
	AQuestTrigger();
	
	UBoxComponent* Trigger;
	UBillboardComponent* BillboardComponent;
protected:

	virtual void BeginPlay() override;
	
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, 
                  AActor* OtherActor, 
                  UPrimitiveComponent* OtherComp, 
                  int32 OtherBodyIndex, 
                  bool bFromSweep, 
                  const FHitResult &SweepResult );

};
