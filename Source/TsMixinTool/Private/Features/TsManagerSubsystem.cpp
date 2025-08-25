// Copyright (c) 2025 Rokukkkk. All rights reserved.

#include "Features/TsManagerSubsystem.h"

#include "TsMixinSettings.h"
#include "Features/TsManagerProxy.h"
#include "Kismet/GameplayStatics.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(TsManagerSubsystem)


static UTsManagerProxy* GlobalTsManagerProxy = nullptr;

void UTsManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const UTsMixinSettings* Settings = GetDefault<UTsMixinSettings>();

	// Start the TS environment
	if (Settings->bTsDebugMode)
	{
		JsEnv = MakeShared<puerts::FJsEnv>(
			std::make_unique<puerts::DefaultJSModuleLoader>(Settings->JsRootDir),
			std::make_unique<puerts::FDefaultLogger>(),
			8091
		);

		if (Settings->bWaitForDebugger)
		{
			JsEnv->WaitDebugger();
		}
	}
	else
	{
		JsEnv = MakeShared<puerts::FJsEnv>();
	}

	const TArray<TPair<FString, UObject*>> Args;
	JsEnv->Start(Settings->JsEntryName, Args);

	// Init ProxyBP
	if (Settings->MixinMode == EMixinMode::ManagerMode)
	{
		const FString ProxyBPPath = TEXT("/TsMixinTool/BP_TsManagerProxy.BP_TsManagerProxy_C");
		const UClass* ProxyClass = StaticLoadClass(UTsManagerProxy::StaticClass(), nullptr, *ProxyBPPath);

		ensure(ProxyClass);

		TsManagerProxy = NewObject<UTsManagerProxy>(this, ProxyClass);

		TsManagerProxy->Initialize();
		GlobalTsManagerProxy = TsManagerProxy;
	}
}

void UTsManagerSubsystem::Deinitialize()
{
	JsEnv.Reset();

	Super::Deinitialize();
}

void UTsManagerSubsystem::ReStartJsEnv()
{
	JsEnv.Reset();
	
	const UTsMixinSettings* Settings = GetDefault<UTsMixinSettings>();
	if (Settings->bTsDebugMode)
	{
		JsEnv = MakeShared<puerts::FJsEnv>(
			std::make_unique<puerts::DefaultJSModuleLoader>(Settings->JsRootDir),
			std::make_unique<puerts::FDefaultLogger>(),
			8091
		);
	
		if (Settings->bWaitForDebugger)
		{
			JsEnv->WaitDebugger();
		}
	}
	else
	{
		JsEnv = MakeShared<puerts::FJsEnv>();
	}
	const TArray<TPair<FString, UObject*>> Args;
	JsEnv->Start(Settings->JsEntryName, Args);

	// Reload level
	if (const UWorld* World = GetWorld())
	{
		FString CurrentLevelName = World->GetMapName();
		CurrentLevelName.RemoveFromStart(World->StreamingLevelsPrefix);

		UGameplayStatics::OpenLevel(World, FName(*CurrentLevelName));
	}
}

UTsManagerProxy* UTsManagerSubsystem::GetProxy()
{
	return GlobalTsManagerProxy;
}

FString UTsManagerSubsystem::GetBPAssetPath(const UObject* Object)
{
	if (const UBlueprintGeneratedClass* BPClass = Cast<UBlueprintGeneratedClass>(Object->GetClass()))
	{
		if (const UBlueprint* BP = Cast<UBlueprint>(BPClass->ClassGeneratedBy))
		{
			return BP->GetPathName().Replace(TEXT("/Game/"), TEXT(""));
		}
	}

	return "";
}
