// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SpeedableInterface.generated.h"

UINTERFACE(MinimalAPI)
class USpeedableInterface : public UInterface
{
	GENERATED_BODY()
	
};

class ISpeedableInterface {
	
	GENERATED_BODY()

public:
	virtual void Applyspeed() = 0;
	virtual void RemoveSpeed() = 0;

};