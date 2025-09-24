// Fill out your copyright notice in the Description page of Project Settings.


#include "NotificationSubsystem.h"

#include "NotificationWidget.h"
#include "Blueprint/UserWidget.h"

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
	UNotificationWidget* Notification = CreateWidget<UNotificationWidget>(GetWorld(), NotificationClass);
	if (!IsValid(Notification))
		return;
	
	Notification->ShowNotification(NotificationText);
	Notification->AddToViewport();
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
