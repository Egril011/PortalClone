// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PressableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UPressableInterface : public UInterface
{
	GENERATED_BODY()
	
};

class IPressableInterface {

	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PressurePlate")
	void OnPlatePressed();
};
