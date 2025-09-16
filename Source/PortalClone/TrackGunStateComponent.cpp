// Fill out your copyright notice in the Description page of Project Settings.

#include "TrackGunStateComponent.h"
#include "GunGrabComponent.h"
#include "GunRecallComponent.h"
#include "GunFreezeComponent.h"

// Sets default values for this component's properties
UTrackGunStateComponent::UTrackGunStateComponent() : GrabComponent(nullptr), RecallComponent(nullptr)
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

		if (UGunGrabComponent* GunGrabComponent = Owner->FindComponentByClass<UGunGrabComponent>()){
			GrabComponent = GunGrabComponent;
		}
		if (UGunRecallComponent* GunRecallComponent = Owner->FindComponentByClass<UGunRecallComponent>())
		{
			RecallComponent = GunRecallComponent;
		}
		if (UGunFreezeComponent* GunFreezeComponent = Owner->FindComponentByClass<UGunFreezeComponent>()){
			FreezeComponent = GunFreezeComponent;
		}
	}
}

void UTrackGunStateComponent::UseCurrentAbility(const FHitResult& HitResult) const
{
	switch (GunState) {
	case EGunStateHandler::Freeze:
		if (bFreezeObject && FreezeComponent)
		{
			FreezeComponent->FreezeObject(HitResult);
		} 
		break;

	case EGunStateHandler::Grab:
		if (bGrabObject && GrabComponent)
		{
			GrabComponent->GrabObject(HitResult);
		}
		break;

	case EGunStateHandler::Recall:
		if (bRecallObject && RecallComponent)
			RecallComponent->Recall(HitResult);
		break;
		
	default:
		break;
	}
}

void UTrackGunStateComponent::ChangeGunState(const EGunStateHandler NewGunState) {
	GunState = NewGunState;
}

void UTrackGunStateComponent::HandleMouseRightInput()
{
	if (GunState == EGunStateHandler::Grab)
	{
		GrabComponent->InputDropObject();
	}
	if (GunState == EGunStateHandler::Recall)
	{
		RecallComponent->CancelRecall();
	}
}