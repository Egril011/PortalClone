// Fill out your copyright notice in the Description page of Project Settings.

#include "GunGrabComponent.h"
#include "PortalCloneGun.h"
#include "GunVFXComponent.h"

// Sets default values for this component's properties
UGunGrabComponent::UGunGrabComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
} 

void UGunGrabComponent::BeginPlay() {

	Super::BeginPlay();
	
	if (AActor* Owner = GetOwner()) {

		if (Owner->IsA<APortalCloneGun>()) {

			GunRef = Cast<APortalCloneGun>(Owner);
		}
	}
}

void UGunGrabComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction) {

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle && PhysicsHandle->GrabbedComponent) {

		//change the object's location so that the location is always the same even though the object is far aways 
		FVector ObjectLocation = GunRef->MuzzleSceneGrabbedObject->GetComponentLocation() +
			(GunRef->MuzzleSceneGrabbedObject->GetComponentRotation().Vector() * 250.0f);

		PhysicsHandle->SetTargetLocation(ObjectLocation);
	}
}

void UGunGrabComponent::GrabObject() {

	if (!GunRef)
	return;

	//if the play have grabbed an object drop it 
	if (PhysicsHandle->GrabbedComponent) {
		DropObject();
		return;
	}

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

			//Call the broadcast
			GunRef->OnShootVFX.Broadcast();

			Primitive->SetSimulatePhysics(true);

			PhysicsHandle->GrabComponentAtLocationWithRotation(
				Primitive,
				GunRef->MuzzleSocketName(),
				Primitive->GetComponentLocation(),
				Primitive->GetComponentRotation()
			);

			Primitive->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
				
			SetComponentTickEnabled(true);
			Activate(true);
		}
	}
}

void UGunGrabComponent::DropObject() {

	if (PhysicsHandle && PhysicsHandle->GrabbedComponent) {

		Primitive->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);

		PhysicsHandle->ReleaseComponent();

		SetComponentTickEnabled(false);
		Deactivate();

		GunRef->OnEndShootVFX.Broadcast();

		Primitive = nullptr;
	}
}

void UGunGrabComponent::ThrowObject() {

	PhysicsHandle->ReleaseComponent();

	Primitive->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);

	Primitive->AddImpulse(GunRef->MuzzleSceneGrabbedObject->GetComponentRotation().Vector()
		* 1000.f * Primitive->GetMass(), NAME_None, false);

	SetComponentTickEnabled(false);
	Deactivate();

	GunRef->OnEndShootVFX.Broadcast();

	Primitive = nullptr;
}

bool UGunGrabComponent::IsHoldingObject() {

	if (PhysicsHandle->GrabbedComponent) {
		ThrowObject();
		return true;
	}

	return false;
}

