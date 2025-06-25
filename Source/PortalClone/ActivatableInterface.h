// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ActivatableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UActivatableInterface : public UInterface
{
	GENERATED_BODY()
	
};

class IActivatableInterface {

	GENERATED_BODY()


public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Activation")
	void Activate();
};