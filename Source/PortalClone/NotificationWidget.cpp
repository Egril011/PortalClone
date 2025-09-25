// Fill out your copyright notice in the Description page of Project Settings.


#include "NotificationWidget.h"
#include "Kismet/GameplayStatics.h"

void UNotificationWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Visible);

	//Set the input also available in the widget
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0))
	{
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		PlayerController->SetInputMode(InputMode);
	}
}

void UNotificationWidget::NativeDestruct()
{
	Super::NativeDestruct();
	
	NotificationTextBlock->SetText(FText::GetEmpty());
	SetVisibility(ESlateVisibility::Hidden);
}

FReply UNotificationWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::SpaceBar)
	{
		OnRequestClose.Broadcast();
		return FReply::Handled();
	}
	
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UNotificationWidget::ShowNotification(const FString& Text) const
{
	if (!IsValid(NotificationTextBlock))
		return;

	NotificationTextBlock->SetText(FText::FromString(Text));
}