// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DMGameJam20231 : ModuleRules
{
	public DMGameJam20231(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "Niagara" });
	}
}
