// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyGameInstance.h"
#include "EGunTimeState.h"
#include "CoreMinimal.h"

class PORTALCLONE_API GunTimeStateHandler
{
public:
	GunTimeStateHandler();
	~GunTimeStateHandler();

	static void ApplyState(AActor* Target, UMyGameInstance* GI);

private:
	static void ApplySlow(AActor* Target);
	static void ApplySpeedUp(AActor* Target);
	static void ApplyFreeze(AActor* Target);
};
