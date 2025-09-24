// Fill out your copyright notice in the Description page of Project Settings.


#include "NotificationWidget.h"

void UNotificationWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Visible);
}

void UNotificationWidget::ShowNotification(const FString& Text) const
{
	if (!IsValid(NotificationTextBlock))
		return;

	NotificationTextBlock->SetText(FText::FromString(Text));
}
