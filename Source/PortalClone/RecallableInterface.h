// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RecallableInterface.generated.h" 

UINTERFACE(MinimalAPI)
class URecallableInterface : public UInterface
{
	GENERATED_BODY()
};

class IRecallableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Recallable")
	void Recallable();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Recallable")
	void CancelRecall();
};
