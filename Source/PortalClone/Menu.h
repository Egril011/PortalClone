// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menu.generated.h"

/**
 * 
 */
UCLASS()
class PORTALCLONE_API UMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRequestClose);
	UPROPERTY()
	FOnRequestClose OnRequestClose;

protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonExit;

	UFUNCTION()
	void OnClickExit();
};
