// Copyright (c) 2025 Rokukkkk. All rights reserved.

#pragma once

#include "UObject/Object.h"

#include "TsManagerProxy.generated.h"


/**
 * The proxy bp for TS mixin
 */
UCLASS(Blueprintable)
class UTsManagerProxy : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void Initialize();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Register(UObject* Object);
};
