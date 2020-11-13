// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Editor/UnrealEd/Public/Toolkits/AssetEditorToolkit.h"
#include "GraphEditor.h"
#include "IDetailsView.h"


/**
 * 
 */
class QUESTSEDITOR_API FQuestSystemBaseEditor : public FAssetEditorToolkit, public FNotifyHook
{
public:

	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;
	// FAssetEditorToolkit
	virtual FName GetToolkitFName() const override { 
		return FName("Quest Editor"); 
	};
	virtual FText GetBaseToolkitName() const override {
		return FText::FromString(FString("Quest Editor"));
	};
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FString GetWorldCentricTabPrefix() const override;

	virtual void InitEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UObject* PropData,TSubclassOf<UEdGraphSchema> Schema);

	TSharedPtr<SGraphEditor> GetGraphEditor() { return GraphEditor; };
protected:
	UObject* PropEdited;
	

	void OnGraphChanged(const FEdGraphEditAction& Action);
	void SelectAllNodes();
	bool CanSelectAllNodes() const;
	void DeleteSelectedNodes();
	bool CanDeleteNode(class UEdGraphNode* Node);
	bool CanDeleteNodes() const;
	void DeleteNodes(const TArray<class UEdGraphNode*>& NodesToDelete);
	void CopySelectedNodes();
	bool CanCopyNodes() const;
	void PasteNodes();
	void PasteNodesHere(const FVector2D& Location);
	bool CanPasteNodes() const;
	void CutSelectedNodes();
	bool CanCutNodes() const;
	void DuplicateNodes();
	bool CanDuplicateNodes() const;
	void DeleteSelectedDuplicatableNodes();
	
	void RenameNodes();
	void OnNodeTitleChanged(const FText& NewText, ETextCommit::Type CommitInfo, UEdGraphNode* NodeBeingChanged);
	bool OnNodeTitleVerification(const FText& NewText, UEdGraphNode* NodeBeingChanged, FText& OutErrorMessage);
	
	void CreateComment();

	/** Called when the selection changes in the GraphEditor */
	void OnSelectedNodesChanged(const TSet<class UObject*>& NewSelection);

	/** Called when a node is double clicked */
	void OnNodeDoubleClicked(class UEdGraphNode* Node);


	TSharedRef<class SGraphEditor> CreateGraphEditorWidget(UEdGraph* InGraph);
	UEdGraphNode * CreateGraphNode(UEdGraph * ParentGraph, TSubclassOf<UEdGraphNode> Class,const FVector2D Location);
	TSharedPtr<SGraphEditor> GraphEditor;
	TSharedPtr<FUICommandList> GraphEditorCommands;
	TSharedPtr<IDetailsView> PropertyEditor;

	TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args);

	FDelegateHandle OnGraphChangedDelegateHandle;

	TSharedPtr<FExtender> ToolbarExtender;
	TSharedPtr<FUICommandList> MyToolBarCommands;
	bool bGraphStateChanged;
	void AddToolbarExtension(FToolBarBuilder &builder);
protected:
	void InitEditor_Internal(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UEdGraph* Graph);
	void OpenBlueprintEditor();
	void PackageGraph();
	virtual UBlueprint* CreateBlueprintScript();
private:
	void CreateStartEndPins(UEdGraph* InGraph);
};

