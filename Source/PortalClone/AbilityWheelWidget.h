// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilityWheelWidget.generated.h"

class UTrackGunStateComponent;

UCLASS()
class PORTALCLONE_API UAbilityWheelWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* AbilityFreeze;

	UPROPERTY(meta = (BindWidget))
	class UButton* AbilityGrab;

	UPROPERTY(meta = (BindWidget))
	class UButton* AbilityRecall;

private:
	UTrackGunStateComponent* GunStateComponent;

	UFUNCTION()
	void OnFreezeClicked();

	UFUNCTION()
	void OnGrabClicked();

	UFUNCTION()
	void OnRecallClicked();
};