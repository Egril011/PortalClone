// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LaserComponent.h"
#include "SlowLaserComponent.generated.h"

class USlowEffectOnPlayer;
/**
 * 
 */
UCLASS(ClassGroup=(Custum), meta=(BlueprintSpawnableComponent))
class PORTALCLONE_API USlowLaserComponent : public ULaserComponent
{          
	GENERATED_BODY()
public:
	USlowLaserComponent();
private:
	virtual void FireLaser() override;
	virtual void StartLaser(AActor* TargetActor) override;
	virtual void LaserEffect() override;

	UPROPERTY(EditAnywhere, Category = "LaserEffect|Variable", meta = (AllowPrivateAccess = "true"))
	float TimerTime = 0.1f;

	UPROPERTY(EditAnywhere, Category = "LaserEffect|Variable", meta = (AllowPrivateAccess = "true"))
	FName LaserEffectParamNameVFX;

	UPROPERTY(EditAnywhere, Category = "LaserEffect|Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USlowEffectOnPlayer> SlowEffectOnPlayer;

	TWeakObjectPtr<AActor> CurrentTargetActor;
	FTimerHandle TimerHandleLaser;
	FVector CurrentTargetLocation;
};
