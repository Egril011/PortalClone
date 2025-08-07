// Fill out your copyright notice in the Description page of Project Settings.

#include "TrackGunStateComponent.h"
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

void UTrackGunStateComponent::UseCurrentAbility(const FHitResult& HitResult) {

	switch (GunState) {
	case EGunStateHandler::Freeze:
		if (CanFreezeObject()) {
			
		}
		break;

	case EGunStateHandler::Grab:
		GrabComponent->GrabObject(HitResult);
		break;

	case EGunStateHandler::Recall:

		break;
		
	default:
		break;
	}
}

void UTrackGunStateComponent::ChangeGunState(EGunStateHandler NewGunState) {
	GunState = NewGunState;
}

