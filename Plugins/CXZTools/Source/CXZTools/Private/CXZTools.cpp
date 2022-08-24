// Copyright Epic Games, Inc. All Rights Reserved.

#include "CXZTools.h"
#include "Interfaces/IPluginManager.h"



#define LOCTEXT_NAMESPACE "FCXZToolsModule"

void FCXZToolsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	bool bLoadDLL = false;
	FString binPath;

#if PLATFORM_64BITS
	binPath = TEXT("/Source/CXZTools/ThirdParty/win64/bin/libxl.dll");
	bLoadDLL = true;
#endif
	libxlhandle = NULL;
	if (bLoadDLL)
	{
		TSharedPtr<IPlugin> FoundModule = IPluginManager::Get().FindPlugin("CXZTools");
		if (FoundModule.IsValid())
		{
			FString path = FoundModule->GetBaseDir();
			FString dllpath = path + binPath;
			libxlhandle = FPlatformProcess::GetDllHandle(*dllpath);
			if (!libxlhandle)
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed to load libxl.dll"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Can't find CXZTools Plugin"));
		}
	}
}

void FCXZToolsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	if (libxlhandle)
	{
		FPlatformProcess::FreeDllHandle(libxlhandle);
	}
}

Format* FCXZToolsModule::TranslateFormat(Book* pBook,const FExcelToolFormat UEFormat)
{
	if(!pBook)
		return NULL;

	Format* format = pBook->addFormat();
	if(!format)
		return NULL;

	libxl::Font* font = pBook->addFont();
	if(!font)
		return NULL;

	//if(m_pCurFormat && font)
	//{
	if(UEFormat.BGColor != EExcelToolColor::ENTRY)
	{
		format->setFillPattern(libxl::FillPattern::FILLPATTERN_SOLID);
		format->setPatternForegroundColor((libxl::Color)UEFormat.BGColor);
	}
	if(UEFormat.FontColor != EExcelToolColor::ENTRY)
	{
		font->setColor((libxl::Color)UEFormat.FontColor);
	}
	if(UEFormat.BorderStyle != EExcelToolBorderStyle::ENTRY)
	{
		format->setBorder((libxl::BorderStyle)UEFormat.BorderStyle);
	}
	if(UEFormat.AlignH != EExcelToolAlignH::ENTRY)
	{
		format->setAlignH((libxl::AlignH)UEFormat.AlignH);
	}
	if(UEFormat.AlignV != EExcelToolAlignV::ENTRY)
	{
		format->setAlignV((libxl::AlignV)UEFormat.AlignV);
	}
	font->setBold(UEFormat.FontBold);
	font->setSize(UEFormat.FontSize);
	format->setFont(font);

	return format;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCXZToolsModule, CXZTools)
