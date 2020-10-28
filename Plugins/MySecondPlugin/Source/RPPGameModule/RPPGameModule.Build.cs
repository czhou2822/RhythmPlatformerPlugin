//------------------ 4.20 VERSION
using UnrealBuildTool;
 
public class RPPGameModule : ModuleRules
{
	public RPPGameModule(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
 
		//Public module names that this module uses.
		//In case you would like to add various classes that you're going to use in your game
		//you should add the core,coreuobject and engine dependencies.
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
 
		//The path for the header files
		PublicIncludePaths.AddRange(new string[] {"RPPGameModule/Public"});
 
		//The path for the source files
		PrivateIncludePaths.AddRange(new string[] {"RPPGameModule/Private"});
	}
}