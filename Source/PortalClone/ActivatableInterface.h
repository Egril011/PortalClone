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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Activation")
	void ShowTheInputToInteract(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
};