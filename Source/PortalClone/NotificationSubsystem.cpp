// Fill out your copyright notice in the Description page of Project Settings.


#include "NotificationSubsystem.h"

#include "NotificationWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void UNotificationSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UNotificationSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

bool UNotificationSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (this->GetClass()->IsInBlueprint() && Super::ShouldCreateSubsystem(Outer))
	{
		return true;
	}
	return false;
}

void UNotificationSubsystem::ShowNotification(const FString& NotificationText)
{
	if (!IsValid(NotificationClass))
		return;
	
	if (!IsValid(Notification))
	{
		Notification = CreateWidget<UNotificationWidget>(GetWorld(), NotificationClass);
	}
	
	Notification->OnRequestClose.AddUniqueDynamic(this, &UNotificationSubsystem::RemoveNotification);
	Notification->ShowNotification(NotificationText);
	Notification->AddToViewport();
}

void UNotificationSubsystem::RemoveNotification()
{
	if (!IsValid(Notification))
		return;
	
	Notification->OnRequestClose.RemoveAll(this);
	Notification->RemoveFromParent();

	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0))
	{
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
	}

	Notification = nullptr;
}

UNotificationSubsystem* UNotificationSubsystem::NotificationSubsystemGetWord(const TObjectPtr<UObject> Object)
{
	if (!IsValid(Object))
		return nullptr;

	if (UWorld* World = Object->GetWorld())
	{
		if (UGameInstance* GameInstance = World->GetGameInstance())
		{
			return GameInstance->GetSubsystem<UNotificationSubsystem>();
		}
	}
	return nullptr;
}
