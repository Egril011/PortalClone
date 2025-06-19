// Fill out your copyright notice in the Description page of Project Settings.

#include "TeleportationCapsule.h"

// Sets default values
ATeleportationCapsule::ATeleportationCapsule()
{
	// add the skeleton mesh to the root
	SkeletonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletonMesh"));
	RootComponent = SkeletonMesh;

	//Attache the collider to the skeleton
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollision->SetupAttachment(SkeletonMesh);
}

void ATeleportationCapsule::OpenDoor() {

	if (!SkeletonMesh->IsPlaying() && AnimOpenDoor) {

		SkeletonMesh->PlayAnimation(AnimOpenDoor, false);
	}

	//Reset the timer
	GetWorld()->GetTimerManager().ClearTimer(TimeHandleCloseDoor);

	//Start the delay to close the door after x sec
	GetWorld()->GetTimerManager().SetTimer(
		TimeHandleCloseDoor,
		this,
		&ATeleportationCapsule::CloseDoor,
		15.0f,
		false
	);
}

void ATeleportationCapsule::CloseDoor() {
	
	if (!SkeletonMesh->IsPlaying() && AnimCloseDoor) {

		SkeletonMesh->PlayAnimation(AnimCloseDoor, false);

		GetWorld()->GetTimerManager().ClearTimer(TimeHandleCloseDoor);
	}
}

