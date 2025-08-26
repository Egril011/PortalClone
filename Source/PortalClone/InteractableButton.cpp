// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractableButton.h"

#include "InteractableTriggerComponent.h"

// Sets default values
AInteractableButton::AInteractableButton()
{
	//add the skeletal mesh to the root
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	RootComponent = SkeletalMesh;

	InteractableTriggerComponent = CreateDefaultSubobject<UInteractableTriggerComponent>(TEXT("TriggerComponent"));
}

void AInteractableButton::Interact_Implementation() {

	PlayAnimation();
}

void AInteractableButton::PlayAnimation() {

	if (!SkeletalMesh->IsPlaying()) {

		SkeletalMesh->PlayAnimation(PressAnimation, false);

		if (ActivatableTarget && ActivatableTarget->Implements<UActivatableInterface>()) {

			IActivatableInterface::Execute_Activate(ActivatableTarget);
		}
	}
}