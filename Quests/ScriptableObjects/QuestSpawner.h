// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TargetPoint.h"
#include "Quests/GenericTypes/ScriptableObject.h"
#include "QuestSpawner.generated.h"

UCLASS()
class QUESTS_API AQuestSpawner : public AScriptableObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuestSpawner();

	AActor* SpawnedActor;
	virtual void Start() override;
	UFUNCTION(BlueprintCallable)
		virtual void Big() override;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> ActorToSpawn;

public:
	UFUNCTION(BlueprintCallable)
		void ClearSpawner();
		void OnActivation_Implementation() override;



};
