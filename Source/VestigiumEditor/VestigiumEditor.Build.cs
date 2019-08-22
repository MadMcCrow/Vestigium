// Noé Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

namespace UnrealBuildTool.Rules
{
	public class VestigiumEditor : ModuleRules
	{
        public VestigiumEditor(ReadOnlyTargetRules Target) : base(Target)
        {

            PrivatePCHHeaderFile = "Public/VestigiumEditor.h";

            //PublicIncludePaths.AddRange(new string[] { "VestigiumEditor/Public" });
            PrivateIncludePaths.AddRange(new string[] { "VestigiumEditor/Private" });

            PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
					"Engine",
                    "InputCore",
                    "AssetTools",
                    "EditorStyle",
					//"LevelEditor",
					"Slate",
                    //"KismetWidgets",
                    //"WorkspaceMenuStructure",
                    "Projects",
                    //"GraphEditor",
                    //"AnimGraph"
                    "Vestigium"
                }
            );

            PrivateDependencyModuleNames.AddRange(
				new string[]
				{					
					"PropertyEditor",
					"SlateCore",
                    "ApplicationCore",
                    "UnrealEd",
                    //"Json",
                    //"JsonUtilities",
                    "Vestigium"
				}
			);

			PrivateIncludePathModuleNames.AddRange(
				new string[] 
				{
					"MainFrame",
					"Settings"
				}
			);

			
		}
	}
}