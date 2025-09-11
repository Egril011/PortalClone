// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalLaserComponent.h"

#include "PortalCloneCharacter.h"
#include "PortalCloneGun.h"
#include "TrackGunStateComponent.h"

void UNormalLaserComponent::FireLaser()
{
	FVector OwnerLocation = GetOwner()->GetActorLocation(); 
	FVector TargetLocation = CurrentTargetActor->GetActorLocation();

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		OwnerLocation,
		TargetLocation,
		ECC_Visibility,
		CollisionParams
		);

	if (bHit)
	{
		DrawDebugLine(
			GetWorld(),
			OwnerLocation,
			HitResult.ImpactPoint,
			FColor::Red,
			false,
			2.f,
			0,
			0.f);
	}
	else
	{
		DrawDebugLine(
			GetWorld(),
			OwnerLocation,
			TargetLocation,
			FColor::Green,
			false,
			2.f,
			0,
			0.f);

		LaserEffect();
	}
	
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

void UNormalLaserComponent::LaserEffect()
{
	// Get the Player and its gun 
	if (CurrentTargetActor->IsA<APortalCloneCharacter>())
	{
		APortalCloneCharacter* Player = Cast<APortalCloneCharacter>(CurrentTargetActor);
		if (!IsValid(Player))
			return;

		APortalCloneGun* EquippedGun = Cast<APortalCloneGun>(Player->EquippedGun);
		if (!IsValid(EquippedGun))
			return;

		//Lock its abilities
		EquippedGun->TrackGunAbility->LockFreezeObject();
		EquippedGun->TrackGunAbility->LockGrabObject();

		UE_LOG(LogTemp,Warning,TEXT("LaserEffect Success"));
	}
}
           