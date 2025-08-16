// Copyright (c) 2025 Rokukkkk. All rights reserved.

#include "Features/TsManagerBlueprintNodes.h"

#include "TsMixinSettings.h"
#include "Features/TsManagerProxy.h"
#include "Features/TsManagerSubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(TsManagerBlueprintNodes)


void UTsManagerBlueprintNodes::RegisterToTsManager(UObject* ContextObject)
{
	if (GetDefault<UTsMixinSettings>()->MixinMode != EMixinMode::ManagerMode)
	{
		UE_LOG(LogTemp, Warning, TEXT("[TsManager] ManagerMode Mode is disabled in project settings."));

#if WITH_EDITOR
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("[TsManager] TsMixinTool is currently in DefaultMode, \"RegisterToTsManager\" node in Blueprint will NOT WORK."));
#endif

		return;
	}

	UTsManagerSubsystem::GetProxy()->Register(ContextObject);
}

void UTsManagerBlueprintNodes::RestartProxy(UObject* ContextObject)
{
	if (ContextObject)
	{
		ContextObject->GetWorld()->GetGameInstance()->GetSubsystem<UTsManagerSubsystem>()->ReStartJsEnv();
	}
	
}
