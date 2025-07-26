// Fill out your copyright notice in the Description page of Project Settings.

#include "GunVFXComponent.h"
#include "PortalCloneGun.h"

// Sets default values for this component's properties
UGunVFXComponent::UGunVFXComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UGunVFXComponent::BeginPlay() {

	Super::BeginPlay();

	if (AActor* Owner = GetOwner()) {

		if (Owner->IsA<APortalCloneGun>()) {

			GunRef = Cast<APortalCloneGun>(Owner);
		}
	}
}

void UGunVFXComponent::StartGunVFXEffect() {

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Work"));

	if (!GunRef) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("GunNull"));
	}
	if (!VFXEffect) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("VFXNull"));
	}

	//looking if there is another effect activate
	if (ActiveVFX) {
		ActiveVFX->Deactivate();
		ActiveVFX->DestroyComponent();
		ActiveVFX = nullptr;
	}

	if (GunRef && VFXEffect) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green,TEXT("Work1")); 
		ActiveVFX = UNiagaraFunctionLibrary::SpawnSystemAttached(
			VFXEffect,
			GunRef->GunSkeletalMesh,
			GunRef->MuzzleSocketName(),
			FVector(0.0f, 0.0f, 0.0f), 
			FRotator(0.0f, 0.0f, 0.0f),
			EAttachLocation::SnapToTarget,
			true
		);
	}
}

void UGunVFXComponent::StopGunVFXEffect() {

	if (VFXEffect) {

		if (ActiveVFX) {
			ActiveVFX->Deactivate();
			ActiveVFX->DestroyComponent();
			ActiveVFX = nullptr;
		}
	}
}

