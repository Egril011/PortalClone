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
	virtual void ApplySlowEffect() = 0;
	virtual void RemoveSlowEffect() = 0;
};