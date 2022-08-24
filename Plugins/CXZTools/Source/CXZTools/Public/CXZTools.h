// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "structs.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

//using namespace IO;


class FCXZToolsModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	Format* TranslateFormat(Book* pBook,const FExcelToolFormat UEFormat);
	void* libxlhandle;
};
