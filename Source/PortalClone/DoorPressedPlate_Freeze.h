// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DoorPressedPlate.h"
#include "FreezableInterface.h"
#include "DoorPressedPlate_Freeze.generated.h"

class UWidgetComponent;
class UFreezeComponent;
/**
 * 
 */
UCLASS()
class PORTALCLONE_API ADoorPressedPlate_Freeze : public ADoorPressedPlate, public IFreezableInterface
{
	GENERATED_BODY()

public:
	ADoorPressedPlate_Freeze();
protected:
	virtual void BeginPlay() override;
	
private:
	void ApplyFreezeEffect_Implementation() override;

	UPROPERTY(EditAnywhere, Category="Component", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UFreezeComponent> FreezeComponent;

	UPROPERTY(VisibleAnywhere, Category="Widget", meta=(AllowPrivateAccess))
	TObjectPtr<UWidgetComponent> WidgetComponent;

	UFUNCTION()
	virtual void PlayCloseDoor() override;
};
