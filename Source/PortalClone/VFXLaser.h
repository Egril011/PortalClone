// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VFXBaseComponent.h"
#include "Components/ActorComponent.h"
#include "VFXLaser.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTALCLONE_API UVFXLaser : public UVFXBaseComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVFXLaser();
	virtual void PlayVFX(FName VFXEffect, FVector TargetLocation) override;
	virtual void StopVFXDelay(float Delay) override;
	virtual void StopVFX() override;
};
