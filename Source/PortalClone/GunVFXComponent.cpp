// Fill out your copyright notice in the Description page of Project Settings.

#include "GunVFXComponent.h"
#include "PortalCloneGun.h"
#include "NiagaraComponent.h"

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

void UGunVFXComponent::PlayVFX(FName VFXEffectName, FVector TargetLocation) {

	//looking if there is another effect activate
	if (ActiveVFX) {
		StopVFX();
	}

	if (GunRef && !VFXMap.IsEmpty()) { 

		if (VFXMap.Contains(VFXEffectName)) {
			ActiveVFX = UNiagaraFunctionLibrary::SpawnSystemAttached(
				VFXMap[VFXEffectName],
				GunRef->GetMesh(),
				GunRef->GetMuzzleSocketName(),
				FVector(0.0f, 0.0f, 0.0f),
				FRotator(0.0f, 0.0f, 0.0f),
				EAttachLocation::SnapToTarget,
				true
			);

			if (ActiveVFX)
			{
				ActiveVFX->SetVectorParameter(TEXT("BeamEnd"), TargetLocation);
			}
		}
	}
}

void UGunVFXComponent::StopVFX() {

	if (ActiveVFX) {
		ActiveVFX->Deactivate();
		ActiveVFX->DestroyComponent();
		ActiveVFX = nullptr;
	}
}

