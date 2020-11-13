using UnrealBuildTool;

public class QuestsEditor : ModuleRules
{
	public QuestsEditor(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        
		PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "InputCore",
            "Engine",
        });

        PrivateDependencyModuleNames.AddRange(new string[] {
            "Slate",
            "SlateCore",
            "PropertyEditor",
            "UnrealEd",
            "EditorStyle",
            "GraphEditor",
            
        });



        PrivateDependencyModuleNames.AddRange(new string[] {"Quests"});
		
		
	}
}
