// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GunStateWidget.generated.h"

class UGunRecallWidget;
class UWidgetSwitcher;
class UGunFreezeWidget;
class UGunGrabWidget;
class UTrackGunStateComponent;
enum class EGunStateHandler : uint8;
/**
 * 
 */
UCLASS()
class PORTALCLONE_API UGunStateWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//Get the TrackGunStateComponent in order to get its broadcast
	void BindGunState(UTrackGunStateComponent* GunStateComponent);

protected:
	virtual void NativeDestruct() override;

private:
	UFUNCTION()
	void UpdateWidgetGunState(EGunStateHandler GunState);

	UPROPERTY(meta=(BindWidget), meta=(AllowPrivateAccess))
	TObjectPtr<UWidgetSwitcher> WidgetSwitcher;
	
	UPROPERTY(meta=(BindWidget), meta=(AllowPrivateAccess))
	TObjectPtr<UGunGrabWidget> GunGrabWidget;

	UPROPERTY(meta=(BindWidget), meta=(AllowPrivateAccess))
	TObjectPtr<UGunFreezeWidget> GunFreezeWidget;

	UPROPERTY(meta=(BindWidget), meta=(AllowPrivateAccess))
	TObjectPtr<UGunRecallWidget> GunRecallWidget;

	TObjectPtr<UTrackGunStateComponent> GunStateComponentInstance;
};
