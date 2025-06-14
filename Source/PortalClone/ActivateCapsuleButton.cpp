// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivateCapsuleButton.h"

// Sets default values
AActivateCapsuleButton::AActivateCapsuleButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//add the skeletal mesh to the root
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	RootComponent = SkeletalMesh;
}

void AActivateCapsuleButton::Interact() {

	PlayAnimation();


}

void AActivateCapsuleButton::PlayAnimation() {

	if (!SkeletalMesh->IsPlaying()){}
		SkeletalMesh->PlayAnimation(AnimSequence, false);
}