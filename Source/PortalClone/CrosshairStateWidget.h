// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CrosshairStateWidget.generated.h"

class APortalCloneCharacter;
class UInteractableCrosshairWidget;
class UNormalCrosshairWidget;
class UWidgetSwitcher;
/**
 * 
 */
UCLASS()
class PORTALCLONE_API UCrosshairStateWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
private:
	//If the player look at an interactable object set the appropriate widget otherwise set the normal widget
	UFUNCTION()
	void UpdateInteractableWidget(bool bIsLooking);

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UWidgetSwitcher> WidgetSwitcher;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UNormalCrosshairWidget> NormalCrosshairWidget;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UInteractableCrosshairWidget> InteractableCrosshairWidget;

	UPROPERTY()
	TObjectPtr<APortalCloneCharacter> Player;
};
