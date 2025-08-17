// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UINTERFACE(MinimalAPI)

class PORTALCLONE_API URecallableInterface : public UInterface
{
	GENERATED_BODY()
};

class IRecallableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void Recallable();
};
