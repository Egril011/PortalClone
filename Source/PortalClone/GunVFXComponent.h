// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "GunVFXComponent.generated.h"

class APortalCloneGun;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTALCLONE_API UGunVFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGunVFXComponent();

public:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void StartGunVFXEffect();

	UFUNCTION()
	void StopGunVFXEffect();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* VFXEffect;

private:
	APortalCloneGun* GunRef;

	UNiagaraComponent* ActiveVFX;
};
