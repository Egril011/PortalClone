// Fill out your copyright notice in the Description page of Project Settings.


#include "FreezeComponent.h"

// Sets default values for this component's properties
UFreezeComponent::UFreezeComponent()
{
}

void UFreezeComponent::StartFreezeEffect()
{
	Owner = GetOwner();
	SetFreezeState(true);

	//Set the Time to decrease the percentage
	StartTime = GetWorld()->GetTimeSeconds();
		
	GetWorld()->GetTimerManager().SetTimer(
		FreezeTimerHandle,
		this,
		&UFreezeComponent::FreezeTimer,
		0.1f,
		true);
}

void UFreezeComponent::FreezeTimer()
{
	float Elapsed = GetWorld()->GetTimeSeconds() - StartTime;
	float Alpha =  Elapsed / Duration;
	Alpha = FMath::Clamp(Alpha,0.f,1.f);

	float inverseAlpha = 1.0f - Alpha;
	OnProgressBarDelegate.Broadcast(inverseAlpha);
	
	if (Alpha >= 1.f)
	{
		GetWorld()->GetTimerManager().ClearTimer(FreezeTimerHandle);
		SetFreezeState(false);
	}
}

void UFreezeComponent::SetFreezeState(bool State) const
{
	if (!IsValid(Owner))
		return;

	if (UStaticMeshComponent* SM = Owner->FindComponentByClass<UStaticMeshComponent>())
	{
		if (State)
		{
			SM->SetMobility(EComponentMobility::Static);
			SM->SetSimulatePhysics(false);
		}
		else
		{
			SM->SetMobility(EComponentMobility::Movable);
			SM->SetSimulatePhysics(true);
		}
	}
}

FOnProgressBarChange* UFreezeComponent::GetProgressBarDelegation()
{
	return &OnProgressBarDelegate;
}