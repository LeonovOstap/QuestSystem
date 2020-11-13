// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSpawner.h"

// Sets default values
AQuestSpawner::AQuestSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AQuestSpawner::Start()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Silver, "Spawned");
	SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, GetActorLocation(),GetActorRotation());
}

void AQuestSpawner::Big()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Silver, "Spawned");
	SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, GetActorLocation(),GetActorRotation());
}

void AQuestSpawner::OnActivation_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Silver, "Spawned");
	SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, GetActorLocation(),GetActorRotation());
}
void AQuestSpawner::ClearSpawner()
{
	if (SpawnedActor)
		SpawnedActor->Destroy();
}