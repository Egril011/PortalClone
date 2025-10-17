// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovingPlatformBase.h"
#include "MovingPlatformNormal.generated.h"

/**
 * 
 */
UCLASS()
class PORTALCLONE_API AMovingPlatformNormal : public AMovingPlatformBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void UpdateMovingPlatform(float DeltaTime) override;

private:
	FVector StartLocation;
	FVector EndLocation;
	FVector TargetLocation;
	bool bPointAOrB;
};