// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorPressedPlate.h"
#include "PressurePlate.h"

// Sets default values
ADoorPressedPlate::ADoorPressedPlate()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	RootComponent = SkeletalMesh;

	DoorState = EDoorAnimation::Close;
}

void ADoorPressedPlate::ArePlateChanged() {

	if (AreAllPlatesActivated()) {
		PlayOpenDoor();
	}
	else {
		PlayCloseDoor();
	}
}

bool ADoorPressedPlate::AreAllPlatesActivated() const {

	for (APressurePlate* Plate : RequiredPressurePlate) {
		
		if (!Plate->IsActivate())
			return false;
	}
	return true;
}

void ADoorPressedPlate::PlayOpenDoor() {

	if (SkeletalMesh && DoorState == EDoorAnimation::Close &&
		!SkeletalMesh->IsPlaying()) {
		
		SkeletalMesh->PlayAnimation(OpenDoorAnimation, false);
		
		DoorState = EDoorAnimation::Open;
	}
}

void ADoorPressedPlate::PlayCloseDoor() {

	if(SkeletalMesh && DoorState == EDoorAnimation::Open &&
		!SkeletalMesh->IsPlaying()){
	
		SkeletalMesh->PlayAnimation(CloseDoorAnimation, false);

		DoorState = EDoorAnimation::Close;
	}
}