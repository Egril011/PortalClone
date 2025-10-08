// Fill out your copyright notice in the Description page of Project Settings.


#include "GunStateWidget.h"
#include "EGunStateHandler.h"
#include "GunFreezeWidget.h"
#include "GunGrabWidget.h"
#include "GunRecallWidget.h"
#include "TrackGunStateComponent.h"
#include "Components/WidgetSwitcher.h"

void UGunStateWidget::BindGunState(UTrackGunStateComponent* GunStateComponent)
{
	if (!IsValid(GunStateComponent))
		return;

	GunStateComponentInstance = GunStateComponent;
	GunStateComponentInstance->OnGunStateChanged.AddUniqueDynamic(this,&UGunStateWidget::UpdateWidgetGunState);
}

void UGunStateWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (IsValid(GunStateComponentInstance))
	{
		GunStateComponentInstance->OnGunStateChanged.RemoveAll(this);
		GunStateComponentInstance = nullptr;
	}
}

void UGunStateWidget::UpdateWidgetGunState(const EGunStateHandler GunState)
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

	case EGunStateHandler::Recall:
		if (IsValid(WidgetSwitcher) && IsValid(GunRecallWidget))
		{
			WidgetSwitcher->SetActiveWidget(GunRecallWidget);
		}
		break;
	default: ;
		WidgetSwitcher->SetActiveWidgetIndex(0);
	}
}
