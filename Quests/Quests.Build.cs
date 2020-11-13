
using UnrealBuildTool;

public class Quests : ModuleRules
{	
	public Quests(ReadOnlyTargetRules Target) : base(Target)
	{

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine"});
    }
}