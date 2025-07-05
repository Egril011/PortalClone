// Fill out your copyright notice in the Description page of Project Settings.

#include "GunGrabComponent.h"
#include "PortalCloneGun.h"

// Sets default values for this component's properties
UGunGrabComponent::UGunGrabComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
} 

void UGunGrabComponent::BeginPlay() {

	Super::BeginPlay();
	GunRef = Cast<APortalCloneGun>(GetOwner());

	SetComponentTickEnabled(true);
	Activate(true);
}

void UGunGrabComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction) {

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UE_LOG(LogTemp, Warning, TEXT("TickComponent firing. Active=%d, Enabled=%d, Registered=%d"),
		IsActive(), IsComponentTickEnabled(), IsRegistered());

	if (GunRef->PhysicsHandle && GunRef->PhysicsHandle->GrabbedComponent) {

		//change the object's location so that the location is always the same even though the object is far aways 
		FVector ObjectLocation = GunRef->MuzzleSceneGrabbedObject->GetComponentLocation() +
			(GunRef->MuzzleSceneGrabbedObject->GetComponentRotation().Vector() * 250.0f);

		GunRef->PhysicsHandle->SetTargetLocation(ObjectLocation);
	}
}

void UGunGrabComponent::GrabObject() {

	if (!GunRef)
	return;

	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, TEXT("GrabAction"));

	//Start the LineTrace
	FVector Start = GunRef->GunSkeletalMesh->
		GetSocketLocation(GunRef->MuzzleSocketName());
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
		DrawDebugLine(GetWorld(), Start, End, FColor::Yellow, false, 10.0f, 0, 1.0f);

		Primitive = HitResult.GetComponent();

		if (Primitive && Primitive->IsSimulatingPhysics()) {

			Primitive->SetSimulatePhysics(true);

			GunRef->PhysicsHandle->GrabComponentAtLocationWithRotation(
				Primitive,
				NAME_None,
				Primitive->GetComponentLocation(),
				Primitive->GetComponentRotation()
			);

			Primitive->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
				
			SetComponentTickEnabled(true);
			Activate(true);
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, TEXT("Test"));
		}
	}
}

void UGunGrabComponent::DropObject() {

	if (GunRef->PhysicsHandle && GunRef->PhysicsHandle->GrabbedComponent) {

		Primitive->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);

		GunRef->PhysicsHandle->ReleaseComponent();

		SetComponentTickEnabled(false);
	}
}

void UGunGrabComponent::ThrowObject() {

	GunRef->PhysicsHandle->ReleaseComponent();

	Primitive->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);

	Primitive->AddImpulse(GunRef->GunSkeletalMesh->
		GetSocketRotation(GunRef->MuzzleSocketName()).Vector()
		* 1000.f * Primitive->GetMass(), NAME_None, false);

	SetComponentTickEnabled(false);
}

