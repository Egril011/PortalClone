// Fill out your copyright notice in the Description page of Project Settings.

#include "GunFireComponent.h"
#include "PortalCloneGun.h"
#include "TrackGunStateComponent.h"
#include "GunGrabComponent.h"

// Sets default values for this component's properties
UGunFireComponent::UGunFireComponent()
{

}

void UGunFireComponent::BeginPlay() {

	Super::BeginPlay();

	if (AActor* Owner = GetOwner())
	{
		if (Owner->IsA<APortalCloneGun>()) {

			GunRef = Cast<APortalCloneGun>(Owner);

			if (GunRef) {
				
				TrackGunAbilityRef = GunRef->TrackGunAbility;
				GrabComponent = GunRef->GunGrabComponent;
			}
		}
	}
}

void UGunFireComponent::Fire() {

	if (!GunRef) {
		return;
	}

	//if the play has grabbed an object
	if (GrabComponent->IsHoldingObject()) {
		return;   
	}

	//Start the LineTrace
	FVector Start = GunRef->GunSkeletalMesh->GetSocketLocation(GunRef->MuzzleSocketName());
	FVector ForwardVector = GunRef->GunSkeletalMesh->
		GetSocketRotation(GunRef->MuzzleSocketName()).Vector();

	FVector End = Start + (ForwardVector * 1000.0f);

	FHitResult HitResult;

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_Visibility
	);

	if (bHit) {
		/*Debug*/
		DrawDebugLine(GetWorld(), Start, End, FColor::Cyan, false, 10.0f, 0, 1.0f);

		//Call the method that will apply the state based on the gun's effect
		TrackGunAbilityRef->UseCurrentAbility(HitResult);
	}
}