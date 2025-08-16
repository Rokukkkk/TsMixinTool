// Copyright Epic Games, Inc. All Rights Reserved.

#include "TsMixinTool.h"

#include "ISettingsModule.h"
#include "TsMixinSettings.h"


#define LOCTEXT_NAMESPACE "FTsMixinToolModule"

void FTsMixinToolModule::StartupModule()
{
	GenerateTs.Register();

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "TsMixinTool",
		                                 FText::FromString("TS Mixin Tool"),
		                                 FText::FromString("Configuration for TS Mixin script generation."),
		                                 GetMutableDefault<UTsMixinSettings>());
	}
}

void FTsMixinToolModule::ShutdownModule()
{
	GenerateTs.Unregister();

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "TsMixinTool");
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FTsMixinToolModule, TsMixinTool)
