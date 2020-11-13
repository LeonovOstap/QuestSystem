
#include "QuestsEditor.h"

#include "KismetEditorUtilities.h"
#include "QuestsEditor/Misc/AssetFactory/QuestAssetActions.h"
#include "QuestsEditor/Editor/UnrealEd_QuestEditorSchema.h"
#include "Engine/Engine.h"


DEFINE_LOG_CATEGORY(QuestsEditor)


void FQuestsEditorModule::StartupModule()
{
	//Register custom assets
    IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	AssetTools.RegisterAdvancedAssetCategory(FName("Quests"), FText::FromString("Quests"));

	AssetTools.RegisterAssetTypeActions(MakeShareable(new FQuestAssetActions()));
	AssetTools.RegisterAssetTypeActions(MakeShareable(new FStorySingletonAssetActions()));
	AssetTools.RegisterAssetTypeActions(MakeShareable(new FObjectiveAssetActions()));

	FToolBarCommandsCommands::Register();

	//Register default BP events
	PrepareGeneratedBlueprintEvents();
}

void FQuestsEditorModule::ShutdownModule()
{
	FKismetEditorUtilities::UnregisterAutoBlueprintNodeCreation(this);
}

void FQuestsEditorModule::PrepareGeneratedBlueprintEvents()
{
	RegisterDefaultEvent(UQuestBlueprintBaseTemplate,EventTick);
	RegisterDefaultEvent(UQuestBlueprintBaseTemplate,OnActivation);
	RegisterDefaultEvent(UQuestBlueprintBaseTemplate,OnCompletion);
}

IMPLEMENT_MODULE(FQuestsEditorModule, QuestsEditor);
