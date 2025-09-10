// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LaserComponent.h"
#include "NormalLaserComponent.generated.h"

/**
 * 
 */
UCLASS()
class PORTALCLONE_API UNormalLaserComponent : public ULaserComponent
{          
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	float TimerTime = 2.f;
	
private:
	virtual void FireLaser() override;
	virtual void StartLaser(AActor* TargetActor) override;

	TWeakObjectPtr<AActor> CurrentTargetActor;
	FTimerHandle TimerHandleLaser;
};
