// Copyright (c) 2025 Rokukkkk. All rights reserved.

#pragma once

#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"


namespace TsMixinToolUtils
{
	inline void ShowSimpleNotification(const FString& Message, const bool bIsSuccess = true, const float Duration = 3.f)
	{
		FNotificationInfo Info(FText::FromString(Message));
		Info.ExpireDuration = Duration;
		Info.bFireAndForget = true;
		Info.bUseThrobber = false;
		Info.bUseSuccessFailIcons = true;

		const TSharedPtr<SNotificationItem> Notification = FSlateNotificationManager::Get().AddNotification(Info);
		if (Notification.IsValid())
		{
			if (bIsSuccess)
			{
				Notification->SetCompletionState(SNotificationItem::CS_Success);
			}
			else
			{
				Notification->SetCompletionState(SNotificationItem::CS_Fail);
			}
		}
	}
}
