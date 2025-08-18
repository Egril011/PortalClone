// Fill out your copyright notice in the Description page of Project Settings.

#include "TrackGunStateComponent.h"
#include "GunGrabComponent.h"
#include "GunRecallComponent.h"
#include "PortalCloneGun.h"

// Sets default values for this component's properties
UTrackGunStateComponent::UTrackGunStateComponent(): GrabComponent(nullptr), GunRef(nullptr)
{
	PrimaryComponentTick.bCanEverTick = false;

	bGrabObject = false;
	bFreezeObject = false;
	bRecallObject = false;
	GunState = EGunStateHandler::Default;
}

void UTrackGunStateComponent::BeginPlay() {

	Super::BeginPlay();

	if (AActor* Owner = GetOwner()) {

		if (Owner->IsA<APortalCloneGun>()) {

			GunRef = Cast<APortalCloneGun>(Owner);

			if (GunRef) {
				GrabComponent = GunRef->GunGrabComponent;
				GunRecallComponent = GunRef->GunRecallComponent;
			}
		}
	}
}

void UTrackGunStateComponent::UseCurrentAbility(const FHitResult& HitResult) const
{
	switch (GunState) {
	case EGunStateHandler::Freeze:
		if (bFreezeObject) {
			
		}
		break;

	case EGunStateHandler::Grab:
		if (bGrabObject && GrabComponent)
		{
			GrabComponent->GrabObject(HitResult);
		}
		break;

	case EGunStateHandler::Recall:
		if (bRecallObject && GunRecallComponent)
			GunRecallComponent->Recall(HitResult);		
		break;
		
	default:
		break;
	}
}

void UTrackGunStateComponent::ChangeGunState(const EGunStateHandler NewGunState) {
	GunState = NewGunState;
}

