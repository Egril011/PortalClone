// Fill out your copyright notice in the Description page of Project Settings.


#include "SlowLaserComponent.h"
#include "PortalCloneCharacter.h"
#include "SlowEffectOnPlayer.h"
#include "VFXLaser.h"

USlowLaserComponent::USlowLaserComponent()
{
	SlowEffectOnPlayer = CreateDefaultSubobject<USlowEffectOnPlayer>(TEXT("SlowEffectOnPlayer"));
}

void USlowLaserComponent::FireLaser()
{
	FVector OwnerLocation = GetOwner()->GetActorLocation(); 

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,   
		OwnerLocation,
		CurrentTargetLocation,
		ECC_Pawn,
		CollisionParams
		);

	//Shoot the VFX
	FVector VFXLocation = bHit ? HitResult.ImpactPoint : CurrentTargetLocation;
	if (IsValid(VFXLaser))
		VFXLaser->PlayVFX(LaserEffectParamNameVFX, VFXLocation);

	if (bHit)
	{
		CurrentTargetActor = HitResult.GetActor();
		LaserEffect();
	}
	
	SetLaserSuccess(true);
	if (IsValid(VFXLaser))
		VFXLaser->StopVFXDelay(2.f);
	OnFireFinished.Broadcast();
}

void USlowLaserComponent::StartLaser(AActor* TargetActor)
{
	//Save the variable and set the Timer to fire the laser
	if (!TargetActor)
	{
		SetLaserSuccess(false);
		OnFireFinished.Broadcast();
	}

	//Get the target location
	CurrentTargetLocation = TargetActor->GetActorLocation();
	
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandleLaser,
		this,
		&USlowLaserComponent::FireLaser,
		TimerTime,
		false
		);
}

void USlowLaserComponent::LaserEffect()
{
	//Slow the player
	if (CurrentTargetActor->IsA<APortalCloneCharacter>())
	{
		if (APortalCloneCharacter* PlayerRef = Cast<APortalCloneCharacter>(CurrentTargetActor))
		{
			if (!IsValid(SlowEffectOnPlayer))
				return;

			SlowEffectOnPlayer->SlowThePlayer(PlayerRef, 30, 5.f);
		}
	}
}
           