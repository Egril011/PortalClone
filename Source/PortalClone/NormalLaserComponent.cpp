// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalLaserComponent.h"

void UNormalLaserComponent::FireLaser()
{
	FVector OwnerLocation = GetOwner()->GetActorLocation();
	FVector TargetLocation = CurrentTargetActor->GetActorLocation();

	DrawDebugLine(
		GetWorld(),
		OwnerLocation,
		TargetLocation,
		FColor::Cyan,
		true,
		2.0f,
		0,
		2.f);

	SetLaserSuccess(true);
	OnFireFinished.Broadcast();
}

void UNormalLaserComponent::StartLaser(AActor* TargetActor)
{
	//Save the variable and set the Timer to fire the laser
	if (!TargetActor)
	{
		SetLaserSuccess(false);
		OnFireFinished.Broadcast();
	}
	
	CurrentTargetActor = TargetActor;

	GetWorld()->GetTimerManager().SetTimer(
		TimerHandleLaser,
		this,
		&UNormalLaserComponent::FireLaser,
		TimerTime,
		false
		);
}
           