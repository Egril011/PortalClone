// Fill out your copyright notice in the Description page of Project Settings.

#include "TrackGunStateComponent.h"
#include "SpeedableInterface.h"
#include "SlowableInterface.h"
#include "GunGrabComponent.h"
#include "PortalCloneGun.h"

// Sets default values for this component's properties
UTrackGunStateComponent::UTrackGunStateComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	bGrabObject = false;
	bThrowObject = false;
	bDropObject = false;
	bFreezeObject = false;
	bSpeedObject = false;
	GunState = EGunStateHandler::Default;
}

void UTrackGunStateComponent::BeginPlay() {

	Super::BeginPlay();

	if (AActor* Owner = GetOwner()) {

		if (Owner->IsA<APortalCloneGun>()) {

			GunRef = Cast<APortalCloneGun>(Owner);

			if (GunRef) {
				GrabComponent = GunRef->GunGrabComponent;
			}
		}
	}
}

void UTrackGunStateComponent::UseCurrentAbility(FHitResult& HitResult) {

	switch (GunState) {
	case EGunStateHandler::Freeze:
		if (CanFreezeObject()) {
			
		}
		break;

	case EGunStateHandler::Grab:
		GrabComponent->GrabObject(HitResult);

	default:
		break;
	}
}

void UTrackGunStateComponent::ChangeGunState(EGunStateHandler NewGunState) {
	GunState = NewGunState;
	if (GEngine)
	{
		FString StateName;

		switch (GunState)
		{
		case EGunStateHandler::Freeze:
			StateName = "Freeze";
			break;
		case EGunStateHandler::Grab:
			StateName = "Grab";
			break;
		case EGunStateHandler::Recall:
			StateName = "Recall";
			break;
		default:
			StateName = "None";
			break;
		}

		GEngine->AddOnScreenDebugMessage(
			-1, // Message key (-1 means add a new message)
			5.0f, // Duration
			FColor::Cyan,
			FString::Printf(TEXT("GunState changed to: %s"), *StateName)
		);
	}
}

