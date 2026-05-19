// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HomeProject : ModuleRules
{
	public HomeProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"HomeProject",
			"HomeProject/Variant_Platforming",
			"HomeProject/Variant_Platforming/Animation",
			"HomeProject/Variant_Combat",
			"HomeProject/Variant_Combat/AI",
			"HomeProject/Variant_Combat/Animation",
			"HomeProject/Variant_Combat/Gameplay",
			"HomeProject/Variant_Combat/Interfaces",
			"HomeProject/Variant_Combat/UI",
			"HomeProject/Variant_SideScrolling",
			"HomeProject/Variant_SideScrolling/AI",
			"HomeProject/Variant_SideScrolling/Gameplay",
			"HomeProject/Variant_SideScrolling/Interfaces",
			"HomeProject/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
