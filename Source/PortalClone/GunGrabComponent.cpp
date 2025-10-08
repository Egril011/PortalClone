// Fill out your copyright notice in the Description page of Project Settings.

#include "GunGrabComponent.h"
#include "PortalCloneGun.h"

// Sets default values for this component's properties
UGunGrabComponent::UGunGrabComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
	MuzzleGrab = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MuzzleGrab"));
} 

TWeakObjectPtr<UGunGrabComponent> UGunGrabComponent::ActiveGrabber = nullptr;

void UGunGrabComponent::BeginPlay() {

	Super::BeginPlay();
	
	if (AActor* Owner = GetOwner()) {

		if (Owner->IsA<APortalCloneGun>()) {

			GunRef = Cast<APortalCloneGun>(Owner);

			//Attach the Muzzle grab to the gun's mesh
			if (IsValid(GunRef))
			{
				MuzzleGrab->AttachToComponent(
					GunRef->GetMesh(),
					FAttachmentTransformRules::SnapToTargetIncludingScale,
					GunRef->GetMuzzleSocketName());
			}
		}
	}
}

void UGunGrabComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction) {

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle && PhysicsHandle->GrabbedComponent) {

		//change the object's location so that the location is always the same even though the object is far always 
		FVector ObjectLocation = MuzzleGrab->GetComponentLocation() +
			(MuzzleGrab->GetComponentRotation().Vector() * 250.0f);

		PhysicsHandle->SetTargetLocation(ObjectLocation);
	}
}

void UGunGrabComponent::GrabObject(const FHitResult& HitResult)
{
	if (!GunRef)
		return;
	
	Primitive = HitResult.GetComponent();

	if (Primitive && Primitive->IsSimulatingPhysics())
	{
		//Call the broadcast to show the VFX
		GunRef->OnShootVFX.Broadcast("Grab", HitResult.ImpactPoint);

		//Start the grab and the tick 
		Primitive->SetSimulatePhysics(true);

		PhysicsHandle->GrabComponentAtLocationWithRotation(
			Primitive,
			GunRef->GetMuzzleSocketName(),
			Primitive->GetComponentLocation(),
			Primitive->GetComponentRotation()
		);

		Primitive->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

		ActiveGrabber = this;
		SetComponentTickEnabled(true);
		Activate(true);
	}
}

void UGunGrabComponent::DropObject() {
	
	if (PhysicsHandle && PhysicsHandle->GrabbedComponent)
	{
		Primitive->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);

		PhysicsHandle->ReleaseComponent();

		SetComponentTickEnabled(false);
		Deactivate();

		GunRef->OnEndShootVFX.Broadcast();
		ActiveGrabber = nullptr;

		Primitive = nullptr;
	}
}

void UGunGrabComponent::InputDropObject()
{
	if (IsHoldingObject())
	{
		DropObject();
	}
}

void UGunGrabComponent::ThrowObject() {

	PhysicsHandle->ReleaseComponent();

	Primitive->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);

	Primitive->AddImpulse(MuzzleGrab->GetComponentRotation().Vector()
		* 1000.f * Primitive->GetMass(), NAME_None, false);

	SetComponentTickEnabled(false);
	Deactivate();

	GunRef->OnEndShootVFX.Broadcast();
	ActiveGrabber = nullptr;

	Primitive = nullptr;
}

bool UGunGrabComponent::IsHoldingObject() const
{
	if (PhysicsHandle->GrabbedComponent) {
		return true;
	}
	
	return false;
}

void UGunGrabComponent::ForceStopGrabIfHoldingObject(UPrimitiveComponent* TargetComponent)
{
	if (!PhysicsHandle || !PhysicsHandle->GrabbedComponent)
		return;

	if (PhysicsHandle->GrabbedComponent == TargetComponent)
	{
		DropObject();
	}
}
