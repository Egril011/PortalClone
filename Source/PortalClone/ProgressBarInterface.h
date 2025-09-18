// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ProgressBarInterface.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProgressBarChange, float, Percentage);
UINTERFACE(MinimalAPI)
class UProgressBarInterface : public UInterface
{
	GENERATED_BODY()
};

class IProgressBarInterface
{
	GENERATED_BODY()

public:
	virtual FOnProgressBarChange* GetProgressBarDelegation() = 0;
};
