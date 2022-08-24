// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
public class CXZTools : ModuleRules
{
	public CXZTools(ReadOnlyTargetRules Target) : base(Target)
	{
//		PrivatePCHHeaderFile = "Public/CXZFuncLib.h";
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
//		bLegacyPublicIncludePaths = true;
//		PCHUsage = ModuleRules.PCHUsageMode.UseSharedPCHs;
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Projects",
				"Json",
				"MediaAssets",
				//"PakFile",
				"RSA",
				
				//"CXZPakFileUtilities",
				"Networking",
				"Sockets",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                //"Projects",
				//"CXZDerivedDataCache",
				//"PakFile",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

		AddEngineThirdPartyPrivateStaticDependencies(Target, "libcurl");
		AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenSSL");

		if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "ThirdParty/include"));
            //   string libpath = Target.Platform == UnrealTargetPlatform.Win32 ? "ThirdParty/Win32/lib" : "ThirdParty/Win64/lib";
            //   string binpath = Target.Platform == UnrealTargetPlatform.Win32 ? "ThirdParty/Win32/bin" : "ThirdParty/Win64/bin";

            string libpath = "ThirdParty/Win64/lib/";
            string binpath = "ThirdParty/Win64/bin/";


            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, libpath,"libxl.lib"));
            PublicSystemLibraryPaths.Add(Path.Combine(ModuleDirectory, binpath));
            PublicDelayLoadDLLs.Add("libxl.dll");
            RuntimeDependencies.Add(Path.Combine(ModuleDirectory, binpath, "libxl.dll"));
            //PublicLibraryPaths.Add(Path.Combine(ModuleDirectory, libpath));
            //PublicAdditionalLibraries.Add("libxl.lib");
            //PublicLibraryPaths.Add(Path.Combine(ModuleDirectory, binpath));
            //PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, binpath, "libxl.dll"));
            //RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(ModuleDirectory, binpath, "libxl.dll")));
            //RuntimeDependencies.Add(Path.Combine(ModuleDirectory, binpath, "libxl.dll"));
        }
    }
}
