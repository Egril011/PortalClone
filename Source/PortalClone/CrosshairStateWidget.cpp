// Fill out your copyright notice in the Description page of Project Settings.


#include "CrosshairStateWidget.h"

#include "InteractableCrosshairWidget.h"
#include "NormalCrosshairWidget.h"
#include "PortalCloneCharacter.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"

void UCrosshairStateWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Player = Cast<APortalCloneCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!IsValid(Player))
		return;

	Player->OnLookAtInteraction.AddUniqueDynamic(this, &UCrosshairStateWidget::UpdateInteractableWidget);

	if (!WidgetSwitcher)
		return;

	WidgetSwitcher->SetActiveWidget(NormalCrosshairWidget);
}

void UCrosshairStateWidget::UpdateInteractableWidget(const bool bIsLooking)
{
	if (!WidgetSwitcher)
		return;

	if (bIsLooking && InteractableCrosshairWidget)
		WidgetSwitcher->SetActiveWidget(InteractableCrosshairWidget);
	else
		WidgetSwitcher->SetActiveWidget(NormalCrosshairWidget);
}
