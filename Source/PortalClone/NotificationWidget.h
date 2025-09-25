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
	void ShowNotification(const FString& Text) const;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRequestClose);
	FOnRequestClose OnRequestClose;
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> NotificationTextBlock;
};
