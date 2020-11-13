// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "Quests/GenericTypes/Objective.h"
#include "SlateBasics.h"
#include "EditorStyleSet.h"
#include "Commands.h"
#include "UnrealEd_QuestEditorActions.h"
#include "UnrealEd_QuestEditorSchema.generated.h"

/**
 * 
 */
UCLASS()
class QUESTSEDITOR_API UnrealEd_BaseEditorSchema : public UEdGraphSchema
{
	GENERATED_BODY()
	protected:
		virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
		virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;
	/*
		virtual void GetContextMenuActions(const UEdGraph* CurrentGraph, const UEdGraphNode* InGraphNode, const UEdGraphPin* InGraphPin, FMenuBuilder* MenuBuilder, bool bIsDebugging) const override;
		virtual class FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const override;*/
		virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override { return FLinearColor::White; };
		virtual bool ShouldHidePinDefaultValue(UEdGraphPin* Pin) const override { return true; };
		virtual TSharedPtr<FEdGraphSchemaAction> GetCreateCommentAction() const override { return TSharedPtr<FEdGraphSchemaAction>(static_cast<FEdGraphSchemaAction*>(new FQuestEdGraphAction_AddComment)); };
		
};
UCLASS()
class QUESTSEDITOR_API UnrealEd_QuestEditorSchema : public UnrealEd_BaseEditorSchema
{
	GENERATED_BODY()
	protected:
		virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
};
/*Rename this to base(we would need to use it for quests)*/
UCLASS()
class QUESTSEDITOR_API UnrealEd_ObjectiveEditorSchema : public UnrealEd_BaseEditorSchema
{
	GENERATED_BODY()
	protected:
		virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
};

UCLASS()
class QUESTSEDITOR_API UnrealEd_StorySingletonEditorSchema : public UnrealEd_BaseEditorSchema
{
	GENERATED_BODY()
	protected:
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
};

class FToolBarCommandsCommands : public TCommands<FToolBarCommandsCommands>
{
public:
	FToolBarCommandsCommands()
		: TCommands<FToolBarCommandsCommands>(TEXT("Open Blueprint Script"), FText::FromString("Open Blueprint Script"), NAME_None, FEditorStyle::GetStyleSetName())
	{
	}
	virtual void RegisterCommands() override;
	TSharedPtr< FUICommandInfo > BPScript;
	TSharedPtr< FUICommandInfo > PackageNode;
};