// Fill out your copyright notice in the Description page of Project Settings.

#include "GunFireComponent.h"
#include "PortalCloneGun.h"
#include "TrackGunStateComponent.h"
#include "GunGrabComponent.h"

// Sets default values for this component's properties
UGunFireComponent::UGunFireComponent()
{

}

void UGunFireComponent::Fire() {

	APortalCloneGun* GunRef = Cast<APortalCloneGun>(GetOwner());
	if (!IsValid(GunRef))
	{
		UE_LOG(LogTemp, Warning, TEXT("Null"))
		return;
	}
	
	/*If the player is firing again,
	// and he has grabbed an object, it will throw it */
	if (IsValid(GunRef->GetGrabComponent()))
	{
		if (GunRef->GetGrabComponent()->IsHoldingObject())
		{
			GunRef->GetGrabComponent()->ThrowObject();
			return;
		}
	}
	
	//Start the LineTrace
	FVector CameraLocation;
	FRotator CameraRotation;

	APortalCloneCharacter* Character = GunRef->GetCharacter();
	
	if (!IsValid(Character))
		return;

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

		FVector Start = CameraLocation;
		FVector ForwardVector = CameraRotation.Vector();

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
			if (IsValid(GunRef->GetTrackGunStateComponent()))
			{
				GunRef->GetTrackGunStateComponent()->UseCurrentAbility(HitResult);
			}
		}
	}
}