// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityWheelComponent.generated.h"

class UAbilityWheelWidget;
class APortalCloneGun;
class UTrackGunStateComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTALCLONE_API UAbilityWheelComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAbilityWheelComponent();

	//Toggle the open or close 
	void ToggleAbilityWheel();
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Widget, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> AbilityWheelClass;;
	
	UAbilityWheelWidget* AbilityWheelInstance = nullptr;

	UFUNCTION()
	void OnClicked();
	
	//Create the Widget
	void CreateAbilityWheel();
};
