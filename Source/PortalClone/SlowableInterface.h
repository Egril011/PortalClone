// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SlowableInterface.generated.h"

UINTERFACE(MinimalAPI)
class USlowableInterface : public UInterface
{
	GENERATED_BODY()
	
};

class ISlowableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ApplySlowEffect();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RemoveSlowEffect();
};