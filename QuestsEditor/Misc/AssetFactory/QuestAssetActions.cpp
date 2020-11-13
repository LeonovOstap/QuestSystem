// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestAssetActions.h"
#include "QuestsEditor/Editor/FlowEditor.h"
#include "QuestsEditor/Editor/UnrealEd_QuestEditorSchema.h"


#define LOCTEXT_NAMESPACE "AssetTypeActions"

/*Quest Asset Actions*/
void FQuestAssetActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		UQuest* PropData = Cast<UQuest>(*ObjIt);
		if (PropData)
		{
			TSharedRef<FQuestSystemBaseEditor> NewEditor(new FQuestSystemBaseEditor());

			NewEditor->InitEditor(Mode,EditWithinLevelEditor,PropData,UnrealEd_QuestEditorSchema::StaticClass());
		}
	}
}

/*Objective Asset Actions*/



void FObjectiveAssetActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		UObjective* PropData = Cast<UObjective>(*ObjIt);
		if (PropData)
		{
			TSharedRef<FQuestSystemBaseEditor> NewEditor(new FQuestSystemBaseEditor());

			NewEditor->InitEditor(Mode,EditWithinLevelEditor,PropData,UnrealEd_ObjectiveEditorSchema::StaticClass());
		}
	}
}

void FStorySingletonAssetActions::OpenAssetEditor(const TArray<UObject*>& InObjects,
	TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		UGameStorySingleton* PropData = Cast<UGameStorySingleton>(*ObjIt);
		if (PropData)
		{
			TSharedRef<FQuestSystemBaseEditor> NewEditor(new FQuestSystemBaseEditor());

			NewEditor->InitEditor(Mode,EditWithinLevelEditor,PropData,UnrealEd_StorySingletonEditorSchema::StaticClass());
		}
	}
}

#undef LOCTEXT_NAMESPACE
