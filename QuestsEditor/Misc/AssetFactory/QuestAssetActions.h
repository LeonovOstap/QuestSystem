// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AssetTypeActions_Base.h"
#include "Quests/GenericTypes/Quest.h"
#include "Quests/GenericTypes/Objective.h"
#include "Quests/GenericTypes/GameStorySingleton.h"
#include "CoreMinimal.h"


/**
 * 
 */
#define CATEGORY FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get().FindAdvancedAssetCategory(FName("Quests"));
class QUESTSEDITOR_API FQuestAssetActions : public FAssetTypeActions_Base
{
	
public:

	//~ FAssetTypeActions_Base overrides

	virtual bool CanFilter() override { return false; };
	virtual uint32 GetCategories() override { return CATEGORY; };
	virtual FText GetName() const override {
		return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_Quest", "Quest");
	};
	virtual UClass* GetSupportedClass() const override { return UQuest::StaticClass(); };
	virtual FColor GetTypeColor() const override { return FColor::Red; };
	virtual bool HasActions(const TArray<UObject*>& InObjects) const override { return false; };
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;

};

class QUESTSEDITOR_API FObjectiveAssetActions : public FAssetTypeActions_Base
{

public:

	//~ FAssetTypeActions_Base overrides

	virtual bool CanFilter() override { return false; };
	virtual uint32 GetCategories() override { return CATEGORY; };
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_Objective", "Objective"); };
	virtual UClass* GetSupportedClass() const override { return UObjective::StaticClass(); };
	virtual FColor GetTypeColor() const override { return FColor::Emerald; };
	virtual bool HasActions(const TArray<UObject*>& InObjects) const override { return false; };
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;

};

class QUESTSEDITOR_API FStorySingletonAssetActions : public FAssetTypeActions_Base
{

	public:

	//~ FAssetTypeActions_Base overrides

	virtual bool CanFilter() override { return false; };
	virtual uint32 GetCategories() override { return CATEGORY; };
	virtual FText GetName() const override { return FText::FromString("Game Singleton"); };
	virtual UClass* GetSupportedClass() const override { return UGameStorySingleton::StaticClass(); };
	virtual FColor GetTypeColor() const override { return FColor::FromHex("#DAA520"); };
	virtual bool HasActions(const TArray<UObject*>& InObjects) const override { return false; };
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;

};



