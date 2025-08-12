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
	
	virtual void BeginPlay() override;

	//method to play the VFX
	UFUNCTION()
	void PlayVFX(FName VFXEffect);

	//method to stop the VFX
	UFUNCTION()
	void StopVFX();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	TMap<FName, UNiagaraSystem*> VFXMap;

private:
	APortalCloneGun* GunRef;

	UNiagaraComponent* ActiveVFX;
};
