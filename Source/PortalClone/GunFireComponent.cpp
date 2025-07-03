// Fill out your copyright notice in the Description page of Project Settings.

#include "PortalCloneGun.h"
#include "MyGameInstance.h"
#include "GunFireComponent.h"

// Sets default values for this component's properties
UGunFireComponent::UGunFireComponent()
{

}

void UGunFireComponent::FireEffect() {

	if (!GunRef)
		return;

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

		AActor* HitActor = HitResult.GetActor();

		UMyGameInstance* GI = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());

		/*Debug*/
		if (GI->CurrentGunState == EGunStateHandler::Freeze) {
			DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 10.0f, 0, 1.0f);
		}
		else {
			DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 10.0f, 0, 1.0f);
		}

		//Call the method that will apply the state based on the gun's effect
	}
}

void UGunFireComponent::InitializeGunRef(APortalCloneGun* GunRef){

	this->GunRef = GunRef;
}