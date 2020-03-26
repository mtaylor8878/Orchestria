using System.IO;

namespace UnrealBuildTool.Rules
{
	public class OrchestriaNetwork : ModuleRules
	{
		public OrchestriaNetwork(ReadOnlyTargetRules Target) : base(Target)
		{
			PrivateIncludePaths.AddRange(
				new string[] {
					"OrchestriaNetwork/Private",
					// ... add other private include paths required here ...
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
				
			PrivateIncludePathModuleNames.AddRange(
			new string[] {
				"Settings",
                "Launch",
            }
            );

            PrivatePCHHeaderFile = "Private/OrchestriaNetworkPrivatePCH.h";

			if (Target.Platform == UnrealTargetPlatform.IOS) {
			}
			else if(Target.Platform == UnrealTargetPlatform.Android)
			{
				string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
                AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(PluginPath, "OrchestriaNetwork_APL.xml")));
            }
        }
	}
}
