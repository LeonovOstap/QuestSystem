// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestAnchor.h"
#include "DrawDebugHelpers.h"

// Sets default values
AQuestAnchor::AQuestAnchor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	BillboardComponent = CreateDefaultSubobject<UBillboardComponent>("Billboard");
}

void AQuestAnchor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	/*DEBUG ONLY*/
	if (GIsEditor && !GIsPlayInEditorWorld)
	{
		TArray<AActor*> ChildActors;

		GetAttachedActors(ChildActors);

		for (AActor* a : ChildActors)
		{
			DrawDebugLine(GetWorld(), GetActorLocation(), a->GetActorLocation(), FColor::Silver, false, 0.f, 0, 5.f);
		}
	}
}

bool AQuestAnchor::ShouldTickIfViewportsOnly() const
{
	return true;
}

void AQuestAnchor::OnActivation_Implementation()
{
	TArray<AActor*> ChildActors;

	GetAttachedActors(ChildActors);

	for (AActor* A : ChildActors)
	{
		if(!A->IsA(AScriptableObject::StaticClass()))
			return;
	
		Cast<AScriptableObject>(A)->ActivateObject();
	}
}
