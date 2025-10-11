// Fill out your copyright notice in the Description page of Project Settings.


#include "VFXLaser.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values for this component's properties
UVFXLaser::UVFXLaser()
{
}

void UVFXLaser::PlayVFX(FName VFXEffect, FVector TargetLocation)
{
	Super::PlayVFX(VFXEffect, TargetLocation);

	ActiveVFX = UNiagaraFunctionLibrary::SpawnSystemAttached(
		VFXMap[VFXEffect],
		GetOwner()->GetRootComponent(),
		NAME_None,
		FVector::ZeroVector,        
		FRotator::ZeroRotator,
		EAttachLocation::KeepRelativeOffset,
		true
	);

	if (!IsValid(ActiveVFX))
		return;
	
	ActiveVFX->SetVectorParameter(TEXT("BeamEnd"), TargetLocation);
}

void UVFXLaser::StopVFXDelay(float Delay)
{
	Super::StopVFXDelay(Delay);
}

void UVFXLaser::StopVFX()
{
	Super::StopVFX();
}

