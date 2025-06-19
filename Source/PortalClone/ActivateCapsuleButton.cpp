// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivateCapsuleButton.h"

// Sets default values
AActivateCapsuleButton::AActivateCapsuleButton()
{
	//add the skeletal mesh to the root
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	RootComponent = SkeletalMesh;
}

void AActivateCapsuleButton::Interact() {

	PlayAnimation();
}

void AActivateCapsuleButton::PlayAnimation() {

	if (!SkeletalMesh->IsPlaying() && TeleportationCapsule) {

		SkeletalMesh->PlayAnimation(AnimSequence, false);

		TeleportationCapsule->OpenDoor();
	}
}