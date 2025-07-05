// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InputAction.h"
#include "PortalCloneCharacter.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/SphereComponent.h"
#include "PortalCloneGun.generated.h"

class UTrackGunStateComponent;
class UGunFireComponent;
class UGunGrabComponent;

UCLASS()
class PORTALCLONE_API APortalCloneGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortalCloneGun();

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FireEffectAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ChangeGunStateAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* GrabObjectAction;

	UPROPERTY(EditAnyWhere)
	USkeletalMeshComponent* GunSkeletalMesh;

	UPROPERTY()
	USceneComponent* MuzzleSceneGrabbedObject;

	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle;

	FName MuzzleSocketName() const { return MuzzleSocketName_; }

protected:
	UPROPERTY()
	USphereComponent* SphereCollider;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

private:
	/** The Character holding this weapon*/
	APortalCloneCharacter* Character;

	//To get the Muzzle'name from the gun's skeleton 
	UPROPERTY(EditAnywhere, Category = "Weapon")
	FName MuzzleSocketName_ = TEXT("Muzzle");

	/** Attaches the actor to a FirstPersonCharacter */
	void AttachWeapon(APortalCloneCharacter* TargetCharacter);

	void UnlockGunInput();

	UPROPERTY()
	UTrackGunStateComponent* TrackGunAbility;

	UPROPERTY()
	UGunFireComponent* GunFireComponent;

	UPROPERTY()
	UGunGrabComponent* GunGrabComponent;

	UPROPERTY()
	bool  bIsEquipped = false;
};
