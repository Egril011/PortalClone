// Fill out your copyright notice in the Description page of Project Settings.

#include "GunVFXComponent.h"
#include "PortalCloneGun.h"
#include "NiagaraComponent.h"

// Sets default values for this component's properties
UGunVFXComponent::UGunVFXComponent()
{
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

	Super::PlayVFX(VFXEffectName, TargetLocation);
	
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

void UGunVFXComponent::StopVFX()
{
	Super::StopVFX();
}

