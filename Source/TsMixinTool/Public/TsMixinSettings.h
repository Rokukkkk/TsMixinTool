// Copyright (c) 2025 Rokukkkk. All rights reserved.

#pragma once

#include "UObject/Object.h"

#include "TsMixinSettings.generated.h"

UENUM()
enum class EMixinMode : uint8
{
	DefaultMode = 0,
	ManagerMode = 1
};


/**
 * The setting menu of this plugin
 */
UCLASS(Config=Game, DefaultConfig, meta=(DisplayName="TS Mixin Tool"))
class UTsMixinSettings : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Config, Category="TS Subsystem")
	FString JsEntryName = TEXT("MainGame");

	UPROPERTY(EditAnywhere, Config, Category="TS Subsystem")
	FString JsRootDir = TEXT("./JaveScript");

	UPROPERTY(EditAnywhere, Config, Category="TS Subsystem")
	bool bTsDebugMode = false;

	UPROPERTY(EditAnywhere, Config, Category="TS Subsystem")
	bool bWaitForDebugger = false;


	UPROPERTY(EditAnywhere, Config, Category="Script Generation", meta=(DisplayName="TS Script Output Path", ToolTip="The path for generating TS script from Blueprint."))
	FString TsScriptOutputPath = TEXT("TypeScript/Source");

	UPROPERTY(EditAnywhere, Config, Category="Script Generation", meta=(DisplayName="Mixin Mode", ToolTip="Change the Mixin mode for generating TS script."))
	EMixinMode MixinMode = EMixinMode::DefaultMode;
};
