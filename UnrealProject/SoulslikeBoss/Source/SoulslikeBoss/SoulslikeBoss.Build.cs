// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SoulslikeBoss : ModuleRules
{
	public SoulslikeBoss(ReadOnlyTargetRules Target) : base(Target)
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
			"SoulslikeBoss",
			"SoulslikeBoss/Variant_Platforming",
			"SoulslikeBoss/Variant_Platforming/Animation",
			"SoulslikeBoss/Variant_Combat",
			"SoulslikeBoss/Variant_Combat/AI",
			"SoulslikeBoss/Variant_Combat/Animation",
			"SoulslikeBoss/Variant_Combat/Gameplay",
			"SoulslikeBoss/Variant_Combat/Interfaces",
			"SoulslikeBoss/Variant_Combat/UI",
			"SoulslikeBoss/Variant_SideScrolling",
			"SoulslikeBoss/Variant_SideScrolling/AI",
			"SoulslikeBoss/Variant_SideScrolling/Gameplay",
			"SoulslikeBoss/Variant_SideScrolling/Interfaces",
			"SoulslikeBoss/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
