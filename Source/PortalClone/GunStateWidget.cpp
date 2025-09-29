// Fill out your copyright notice in the Description page of Project Settings.


#include "GunStateWidget.h"
#include "EGunStateHandler.h"
#include "GunFreezeWidget.h"
#include "GunGrabWidget.h"
#include "TrackGunStateComponent.h"
#include "Components/WidgetSwitcher.h"

void UGunStateWidget::BindGunState(UTrackGunStateComponent* GunStateComponent)
{
	if (!IsValid(GunStateComponent))
		return;
	
	GunStateComponent->OnGunStateChanged.AddUniqueDynamic(this,&UGunStateWidget::UpdateWidgetGunState);
}

void UGunStateWidget::UpdateWidgetGunState(EGunStateHandler GunState)
{
	switch (GunState)
	{
	case EGunStateHandler::Grab:
		if (IsValid(WidgetSwitcher) && IsValid(GunGrabWidget))
		{
			WidgetSwitcher->SetActiveWidget(GunGrabWidget);
		}
		break;
		
	case EGunStateHandler::Freeze:
		if (IsValid(WidgetSwitcher) && IsValid(GunFreezeWidget))
		{
			WidgetSwitcher->SetActiveWidget(GunFreezeWidget);
		}
		break;
	default: ;
		WidgetSwitcher->SetActiveWidgetIndex(0);
	}
}
