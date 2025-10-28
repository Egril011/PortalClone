// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "VFXBaseComponent.h"
#include "GunVFXComponent.generated.h"

class APortalCloneGun;
class UNiagaraComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PORTALCLONE_API UGunVFXComponent : public UVFXBaseComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGunVFXComponent();
	
	virtual void BeginPlay() override;

	virtual void PlayVFX(FName VFXEffect, FVector TargetLocation) override;
	virtual void StopVFX() override;
	
private:
	APortalCloneGun* GunRef;
};
