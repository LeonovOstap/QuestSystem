// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface.h"
#include "ActivatableInterface.generated.h"

/**
 * 
 */
UINTERFACE()
class QUESTS_API UActivatableInterface : public UInterface
{
 GENERATED_BODY()
};

class QUESTS_API IActivatableInterface
{
 GENERATED_BODY()
 public:
           virtual void SetActive(bool bIsActive);
           virtual bool GetIsActive() const;
};