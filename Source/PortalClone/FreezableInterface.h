// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FreezableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UFreezableInterface : public UInterface
{
	GENERATED_BODY()
	
};

class IFreezableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="FreezeInterface")
	void ApplyFreezeEffect();
};