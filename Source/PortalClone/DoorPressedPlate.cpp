// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorPressedPlate.h"
#include "PressurePlate.h"

// Sets default values
ADoorPressedPlate::ADoorPressedPlate()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	RootComponent = SkeletalMesh;
}

void ADoorPressedPlate::AreAllPlatesActivated() {

	for (APressurePlate* Plate : RequiredPressurePlate) {
		
		if (!Plate->IsActivate())
			return;
	}

	_isOpen = true;
	PlayOpenDoor();
}

void ADoorPressedPlate::PlayOpenDoor() {

	if (SkeletalMesh && !SkeletalMesh->IsPlaying()) {
		
		SkeletalMesh->PlayAnimation(OpenDoorAnimation, false);
	}
}

void ADoorPressedPlate::PlayCloseDoor() {

	if(SkeletalMesh && !SkeletalMesh->IsPlaying() && _isOpen == true){
	
		SkeletalMesh->PlayAnimation(CloseDoorAnimation, false);

		_isOpen = false;
	}
}

