// Copyright (c) 2025 Rokukkkk. All rights reserved.

#pragma once

#include "JsEnv.h"
#include "UObject/Object.h"

#include "TsManagerSubsystem.generated.h"

class UTsManagerProxy;


/**
 * The main subsystem for initialize JsEnv and handling TS things.
 */
UCLASS()
class TSMIXINTOOL_API UTsManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable)
	void ReStartJsEnv();

	UFUNCTION()
	static UTsManagerProxy* GetProxy();

	UFUNCTION()
	static FString GetBPAssetPath(const UObject* Object);

private:
	TSharedPtr<puerts::FJsEnv> JsEnv;

	UPROPERTY()
	TObjectPtr<UTsManagerProxy> TsManagerProxy;
};
