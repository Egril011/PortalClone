// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "NotificationWidget.generated.h"

UCLASS()
class PORTALCLONE_API UNotificationWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void ShowNotification(const FString& Text) const;
	
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> NotificationTextBlock;
};
