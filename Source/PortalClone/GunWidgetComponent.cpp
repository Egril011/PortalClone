// Fill out your copyright notice in the Description page of Project Settings.


#include "GunWidgetComponent.h"

#include "GunStateWidget.h"
#include "TrackGunStateComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UGunWidgetComponent::UGunWidgetComponent()
{
}

void UGunWidgetComponent::InitializeWidget(UTrackGunStateComponent* TrackGunStateComponent)
{
	if (!IsValid(GunWidget) || !IsValid(TrackGunStateComponent))
		return;

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!IsValid(PlayerController))
		return;

	//If the widget is still in live destroy it 
	if (IsValid(UserWidgetInstance))
	{
		UserWidgetInstance->RemoveFromParent();
		UserWidgetInstance = nullptr;
	}
	
	UserWidgetInstance = CreateWidget<UGunStateWidget>(PlayerController, GunWidget);
	if (!IsValid(UserWidgetInstance))
		return;

	UserWidgetInstance->BindGunState(TrackGunStateComponent);
	UserWidgetInstance->AddToViewport();
}

void UGunWidgetComponent::DestroyComponent(bool bPromoteChildren)
{
	Super::DestroyComponent(bPromoteChildren);

	if (IsValid(UserWidgetInstance))
	{
		UserWidgetInstance->RemoveFromParent();
		UserWidgetInstance = nullptr;
	}
}