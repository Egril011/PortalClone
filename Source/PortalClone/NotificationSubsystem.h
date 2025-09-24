// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "NotificationSubsystem.generated.h"

class UNotificationWidget;

UCLASS(Blueprintable, BlueprintType)
class PORTALCLONE_API UNotificationSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	void ShowNotification(const FString& NotificationText);
	static UNotificationSubsystem* NotificationSubsystemGetWord(const TObjectPtr<UObject> Object);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UNotificationWidget> NotificationClass;
};
