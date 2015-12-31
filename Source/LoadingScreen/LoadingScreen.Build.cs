// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class LoadingScreen : ModuleRules
	{
		public LoadingScreen(TargetInfo Target)
		{
			PrivateIncludePaths.Add("LoadingScreen/Private");

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
					"MoviePlayer",
					"Slate",
					"SlateCore",
					"InputCore",
					"Engine"
				}
				);
		}
	}
}
