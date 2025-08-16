// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Features/BlueprintAssetAction_GenerateTs.h"
#include "Modules/ModuleManager.h"


class FTsMixinToolModule final : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	FBlueprintAssetAction_GenerateTs GenerateTs;
};
