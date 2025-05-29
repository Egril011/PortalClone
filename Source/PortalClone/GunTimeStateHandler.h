// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyGameInstance.h"
#include "EGunTimeState.h"
#include "SlowableInterface.h"
#include "SpeedableInterface.h"
#include "CoreMinimal.h"

class PORTALCLONE_API GunTimeStateHandler
{
public:
	GunTimeStateHandler();
	~GunTimeStateHandler();

	static void ApplyState(AActor* Target, UMyGameInstance* GI);

private:
	static void SlowEffect(AActor* Target);
	static void SpeedUpEffect(AActor* Target);
};
