// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphPin.h"
#include "QuestsEditor/Editor/Graph/UnrealEd_QuestPinNodes.h"
#include "QuestsEditor/Editor/Graph/UnrealEd_QuestGraph.h"
#include "Nodes/GraphNodeImplementations.h"
#include "UObject/NoExportTypes.h"
#include "NodeCompiler.generated.h"

/**
 * 
 */

DECLARE_LOG_CATEGORY_EXTERN(LogQuestNodeCompiler, All, All);

USTRUCT()
struct QUESTSEDITOR_API FNodeCompiler
{
	GENERATED_BODY()
		public:
			static FNodeCompiler Get() { return FNodeCompiler();};
			
			void LinkPins(UPackagedNodeData* Package);
			void PackageNode(UPackagedNodeData* PackagedNodeData,UExecutionGraph* Graph);
			void PackageGraph(UnrealEd_BaseQuestGraph* Graph);
			
		private:
			UPackagedNodeData* CreatePackagedNode(UQuestBaseNode* Node,UExecutionGraph* Graph);
			UPackagedPin* CreatePackagedPin(UEdGraphPin* Pin, UPackagedNodeData* Node);
			UPackagedPin* FindPackagedPinByGuidInNodes(FGuid Guid);
			UEdGraphPin* FindPinByGuidInNodes(FGuid Guid);
			void PackageGraph_Internal(UnrealEd_BaseQuestGraph* Graph);

			void TransferProperties(UQuestBaseNode* From, UPackagedNodeData* To);
	
};

