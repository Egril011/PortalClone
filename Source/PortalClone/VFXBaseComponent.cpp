// Fill out your copyright notice in the Description page of Project Settings.


#include "VFXBaseComponent.h"
#include "NiagaraComponent.h"

// Sets default values for this component's properties
UVFXBaseComponent::UVFXBaseComponent()
{
	
}

void UVFXBaseComponent::PlayVFX(FName VFXEffect, FVector TargetLocation)
{
	if (ActiveVFX)
		StopVFX();
}

void UVFXBaseComponent::StopVFX()
{
	if (ActiveVFX) {
		ActiveVFX->Deactivate();
		ActiveVFX->DestroyComponent();
		ActiveVFX = nullptr;
	}
}

void UVFXBaseComponent::StopVFXDelay(float Delay)
{
	GetWorld()->GetTimerManager().ClearTimer(VFXDelayTimer);
	GetWorld()->GetTimerManager().SetTimer(
		VFXDelayTimer,
		this,
		&UVFXBaseComponent::StopVFX,
		Delay,
		false);
}

