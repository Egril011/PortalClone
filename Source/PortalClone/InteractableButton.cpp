// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableButton.h"

// Sets default values
AInteractableButton::AInteractableButton()
{
	//add the skeletal mesh to the root
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	RootComponent = SkeletalMesh;
}

void AInteractableButton::Interact_Implementation() {

	PlayAnimation();
}

void AInteractableButton::PlayAnimation() {

	if (!SkeletalMesh->IsPlaying()) {

		SkeletalMesh->PlayAnimation(AnimSequence, false);

		if (TargetActor && TargetActor->Implements<UActivatableInterface>()) {

			IActivatableInterface::Execute_Activate(TargetActor);
		}
	}
}