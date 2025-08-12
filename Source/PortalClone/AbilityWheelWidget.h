// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilityWheelWidget.generated.h"

class UTrackGunStateComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRequestClose);

UCLASS()
class PORTALCLONE_API UAbilityWheelWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;\
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	//BroadCast
	UPROPERTY(BlueprintAssignable, Category="Event")
	FOnRequestClose OnRequestClose;

protected:
	//Change the gun's state for the freeze
	UPROPERTY(meta = (BindWidget))
	class UButton* AbilityFreeze;

	//Change the gun's state for the grab
	UPROPERTY(meta = (BindWidget))
	class UButton* AbilityGrab;

	//Change the gun's state for the recall
	UPROPERTY(meta = (BindWidget))
	class UButton* AbilityRecall;

private:
	UFUNCTION()
	void OnFreezeClicked();

	UFUNCTION()
	void OnGrabClicked();

	UFUNCTION()
	void OnRecallClicked();

	void SetupAbility(UButton* Button, bool bIsUnlocked, FName HandlerName);

	UTrackGunStateComponent*  TrackGunAbility;
};