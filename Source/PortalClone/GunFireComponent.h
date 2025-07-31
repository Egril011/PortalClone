// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GunFireComponent.generated.h"

class APortalCloneGun;
class UTrackGunStateComponent;
class UGunGrabComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTALCLONE_API UGunFireComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGunFireComponent();

	//method to shot the effect
	void Fire();

protected: 

	virtual void BeginPlay() override;

private: 
	UPROPERTY()
	APortalCloneGun* GunRef;

	UPROPERTY()
	UTrackGunStateComponent* TrackGunAbilityRef;

	UPROPERTY()
	UGunGrabComponent* GrabComponent; 
};
