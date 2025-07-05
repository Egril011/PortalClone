// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EGunStateHandler.h"
#include "TrackGunStateComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTALCLONE_API UTrackGunStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTrackGunStateComponent();
	
	/*Encapuslation and the methodes to unlcok or lock an ability*/
	bool CanGrabObject() const { return bGrabObject; }
	void UnlockGrabObject() { bGrabObject = true; }
	void LockGrabObject() { bGrabObject = false; }

	bool CanThrowObject() const { return bThrowObject; }
	void UnlockThrowObject() { bThrowObject = true; }
	void LockThrowObject() { bThrowObject = false; }

	bool CanDropObject() const { return bDropObject; }
	void UnlockDropObject() { bDropObject = true; }
	void LockDropObject() { bDropObject = false; }

	bool CanFreezeObject() const { return bFreezeObject; }
	void UnlockFreezeObject() { bFreezeObject = true; }
	void LockFreezeObject() { bFreezeObject = false; }

	bool CanSpeedObject() const { return bSpeedObject; }
	void UnlockSpeedObject() { bSpeedObject = true; }
	void LockSpeedObect() { bSpeedObject = false; }

	//Apply the appropriate effect depending on the gun's state
	void ApplyEffect(AActor* Target);

	//Change the Gun's state
	void ChangeGunEffect();

private:
	bool bGrabObject;
	bool bThrowObject;
	bool bDropObject;
	bool bFreezeObject;
	bool bSpeedObject;

	EGunStateHandler GunState;

	void ApplyFreezeEffect(AActor* Target);
	void ApplySpeedUpEffect(AActor* Target);
};
