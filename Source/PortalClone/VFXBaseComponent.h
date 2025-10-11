// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VFXBaseComponent.generated.h"


class UNiagaraSystem;
class UNiagaraComponent;

UCLASS(Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTALCLONE_API UVFXBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVFXBaseComponent();

protected:
	//method to play the VFX
	UFUNCTION()
	virtual void PlayVFX(FName VFXEffect, FVector TargetLocation);

	//method to stop the VFX
	UFUNCTION()
	virtual void StopVFX();

	//Stop the VFX after X time
	UFUNCTION()
	virtual void StopVFXDelay(float Delay);
	
	UPROPERTY(EditAnywhere, Category="VFX", meta = (AllowPrivateAccess = "true"))
	TMap<FName, TObjectPtr<UNiagaraSystem>> VFXMap;

	TObjectPtr<UNiagaraComponent> ActiveVFX;

private:
	FTimerHandle VFXDelayTimer;
};
