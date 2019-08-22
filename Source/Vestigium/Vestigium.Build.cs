// Copyright 2019 Noé Perard-Gayot All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class Vestigium : ModuleRules
	{
		public Vestigium(ReadOnlyTargetRules Target) : base(Target)
		{
            PrivatePCHHeaderFile = "Public/Vestigium.h";

            // paths
            //PublicIncludePaths.AddRange(new string[] { "Vestigium/Public" });
            PrivateIncludePaths.AddRange(new string[] { "Vestigium/Private" });


            PublicIncludePaths.AddRange(
				new string[] {
					// ... add public include paths required here ...
				}
				);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
                    "Engine"
					// ... add other public dependencies that you statically link with here ...
				}
				);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					// ... add private dependencies that you statically link with here ...
				}
				);

			DynamicallyLoadedModuleNames.AddRange(
				new string[]
				{
					// ... add any modules that your module loads dynamically here ...
				}
				);
		}
	}
}
