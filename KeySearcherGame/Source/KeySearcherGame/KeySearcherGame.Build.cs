// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class KeySearcherGame : ModuleRules
{
	public KeySearcherGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] 
		{
            "KeySearcherGame/Public/Characters",
            "KeySearcherGame/Public/Gamemodes",
            "KeySearcherGame/Public/Learn/Characters",
            "KeySearcherGame/Public/UI/HUDs",
            "KeySearcherGame/Public/UI/Widgets",
        });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
