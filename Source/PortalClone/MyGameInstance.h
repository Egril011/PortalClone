// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "EGunTimeState.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PORTALCLONE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

	public:
		EGunTimeState CurrentGunState = EGunTimeState::None; 
};
