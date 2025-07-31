// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EGunStateHandler.h"
#include "TrackGunStateComponent.generated.h"

class UGunGrabComponent;
class APortalCloneGun;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTALCLONE_API UTrackGunStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTrackGunStateComponent();
	
	/*Encapsulation and the methods to unlock or lock an ability*/
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
	void LockSpeedObject() { bSpeedObject = false; }

	//Apply the appropriate effect depending on the gun's state
	void UseCurrentAbility(FHitResult& HitResult);

	//Change the Gun's state
	void ChangeGunState(EGunStateHandler NewGunState);

protected:
	virtual void BeginPlay() override;

private:
	bool bGrabObject;
	bool bThrowObject;
	bool bDropObject;
	bool bFreezeObject;
	bool bSpeedObject;

	EGunStateHandler GunState;
	UGunGrabComponent* GrabComponent;
	APortalCloneGun* GunRef;
};
