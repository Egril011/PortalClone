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
	virtual void FireLaser() override;
};
