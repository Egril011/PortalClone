// Fill out your copyright notice in the Description page of Project Settings.

#include "GunFireComponent.h"
#include "PortalCloneGun.h"
#include "TrackGunStateComponent.h"

// Sets default values for this component's properties
UGunFireComponent::UGunFireComponent()
{

}

void UGunFireComponent::BeginPlay() {

	Super::BeginPlay();

	if (AActor* O = GetOwner())
	{
		UE_LOG(LogTemp, Warning, TEXT("UGunFireComponent::BeginPlay – Owner = %s (%s)"),
			*O->GetName(), *O->GetClass()->GetName());
	}

	GunRef = Cast<APortalCloneGun>(GetOwner());

	if (!GunRef)
	{
		UE_LOG(LogTemp, Error, TEXT("UGunFireComponent: Failed to cast Owner to APortalCloneGun!"));
		return;
	}
}

void UGunFireComponent::FireEffect() {

	if (!GunRef) {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, TEXT("nullptd"));
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

		AActor* HitActor = HitResult.GetActor();

		/*Debug*/
		DrawDebugLine(GetWorld(), Start, End, FColor::Cyan, false, 10.0f, 0, 1.0f);

		//Call the method that will apply the state based on the gun's effect
	}
}