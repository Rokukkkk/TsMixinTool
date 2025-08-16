// Copyright (c) 2025 Rokukkkk. All rights reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "TsManagerBlueprintNodes.generated.h"


UCLASS()
class TSMIXINTOOL_API UTsManagerBlueprintNodes : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="TsManager", meta=(DefaultToSelf=ContextObject))
	static void RegisterToTsManager(UObject* ContextObject);

	UFUNCTION(BlueprintCallable, Category="TsManager")
	static void RestartProxy(UObject* ContextObject);
};
