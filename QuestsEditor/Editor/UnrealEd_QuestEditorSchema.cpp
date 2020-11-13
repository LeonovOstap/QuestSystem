// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealEd_QuestEditorSchema.h"
#include "QuestsEditor/Editor/Graph/UnrealEd_QuestPinNodes.h"


void UnrealEd_QuestEditorSchema::GetGraphContextActions(FGraphContextMenuBuilder & ContextMenuBuilder) const
{
	Super::GetGraphContextActions(ContextMenuBuilder);
	for (TObjectIterator<UObjective> It; It; ++It)
	{
		TSharedPtr<FObjectiveContextAction> ObjectiveContext = TSharedPtr<FObjectiveContextAction>(new FObjectiveContextAction(
			FText::FromString("Objectives"),
			FText::FromString(FString("Reference Objective ").Append(It->GetName())),
			FText(),
			0));
		ObjectiveContext->NodeTemplate = *It;
		ContextMenuBuilder.AddAction(ObjectiveContext);
	}
}

void UnrealEd_ObjectiveEditorSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	Super::GetGraphContextActions(ContextMenuBuilder);
	for(TObjectIterator<AScriptableObject> It;It;++It)
	{
		TSharedPtr<FScriptableObjectContextAction> ScriptContext = TSharedPtr<FScriptableObjectContextAction>(new FScriptableObjectContextAction(
        FText::FromString("Scriptable Objects"),
        FText::FromString(FString("Add Node Referencing -> ").Append(It->GetName())),
        FText(),
        0));
		ScriptContext->NodeClass = UScriptableNode::StaticClass();
		ScriptContext->Actor = *It;
		ContextMenuBuilder.AddAction(ScriptContext);
	}

	TSharedPtr<FBPExecutorContextAction> ExecutorContext = TSharedPtr<FBPExecutorContextAction>(new FBPExecutorContextAction(
		FText::FromString("Execute Events"),
		FText::FromString(FString("Add Node")),
		FText(),
		0));
	ExecutorContext->NodeClass = UEventExecutorNode::StaticClass();
	ContextMenuBuilder.AddAction(ExecutorContext);

}

void UnrealEd_StorySingletonEditorSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	Super::GetGraphContextActions(ContextMenuBuilder);
}

void UnrealEd_BaseEditorSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	TSharedPtr<FAddNodeContextAction> RuleContext = TSharedPtr<FAddNodeContextAction>(new FAddNodeContextAction(
		FText::FromString("Add Node"),
		FText::FromString("Add Rule Node"),
		FText(),
		0,
		URuleNode::StaticClass()));
	ContextMenuBuilder.AddAction(RuleContext);
}

const FPinConnectionResponse UnrealEd_BaseEditorSchema::CanCreateConnection(const UEdGraphPin * A, const UEdGraphPin * B) const
{
	// Make sure the input is connecting to an output
	if (A->Direction == B->Direction)
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Not allowed"));

	// Make sure the data types match
	if (A->PinType.PinCategory != B->PinType.PinCategory)
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Not allowed"));
	

	if(A->GetOwningNode() == B->GetOwningNode())
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Not allowed"));

	if((A->Direction == EGPD_Input && A->LinkedTo.Num() > 0)
		|| (B->Direction == EGPD_Input && B->LinkedTo.Num() > 0))
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Not allowed"));

	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, TEXT(""));
}

#define LOCTEXT_NAMESPACE "UICustom"
void FToolBarCommandsCommands::RegisterCommands()
{
	UI_COMMAND(BPScript, "Open Blueprint Script", "Open Blueprint Script", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(PackageNode,"Package Graph","Package Graph Execution Data",EUserInterfaceActionType::Button,FInputChord());
}
#undef LOCTEXT_NAMESPACE


