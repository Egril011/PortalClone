// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EGunStateHandler.h"
#include "TrackGunStateComponent.generated.h"

class UGunRecallComponent;
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
	
	bool CanFreezeObject() const { return bFreezeObject; }
	void UnlockFreezeObject() { bFreezeObject = true; }
	void LockFreezeObject() { bFreezeObject = false; }

	bool CanRecallObject() const { return bRecallObject; }
	void UnlockRecallObject() { bRecallObject = true; }
	void LockRecallObject() { bRecallObject = false; }

	//Apply the appropriate effect depending on the gun's state
	void UseCurrentAbility(const FHitResult& HitResult) const;

	//Change the Gun's state
	void ChangeGunState(EGunStateHandler NewGunState);

protected:
	virtual void BeginPlay() override;

private:
	bool bGrabObject;
	bool bFreezeObject;
	bool bRecallObject;

	EGunStateHandler GunState;
	UGunGrabComponent* GrabComponent;
	UGunRecallComponent* GunRecallComponent;
	APortalCloneGun* GunRef;
};
