// Copyright (c) 2025 Rokukkkk. All rights reserved.

using UnrealBuildTool;

public class TsMixinTool : ModuleRules
{
	public TsMixinTool(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			[
				"Core",
				"JsEnv"
			]
		);

		PrivateDependencyModuleNames.AddRange(
			[
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"Settings"
			]
		);
	}
}