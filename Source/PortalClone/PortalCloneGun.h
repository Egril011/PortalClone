// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InputAction.h"
#include "PortalCloneCharacter.h"
#include "Components/SphereComponent.h"
#include "Delegates/Delegate.h"
#include "Blueprint/UserWidget.h"
#include "PortalCloneGun.generated.h"

class UTrackGunStateComponent;
class UGunFireComponent;
class UGunGrabComponent;
class UGunVFXComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShootVFX, FName, VFXName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndShootVFX);

class UAbilityWheelWidget;

UCLASS()
class PORTALCLONE_API APortalCloneGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortalCloneGun();

	//Skeleton
	UPROPERTY(EditAnyWhere)
	USkeletalMeshComponent* GunSkeletalMesh;

	/*BroadCast*/
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnShootVFX OnShootVFX;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnEndShootVFX OnEndShootVFX;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ChangeGunStateAction;
	
	/*Gun Components*/
	UPROPERTY(EditAnywhere, Category = "GunComponent")
	UTrackGunStateComponent* TrackGunAbility;

	UPROPERTY(EditAnywhere, Category = "GunComponent")
	UGunFireComponent* GunFireComponent;

	UPROPERTY(EditAnywhere, Category = "GunComponent")
	UGunGrabComponent* GunGrabComponent;

	UPROPERTY(EditAnywhere, Category = "GunComponent")
	UGunVFXComponent* GunVFXComponent;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	USceneComponent* MuzzleSceneGrabbedObject;

	FName MuzzleSocketName() const { return MuzzleSocketName_; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Widget)
	TSubclassOf<UUserWidget> AbilityWheelWidgetClass;

	UAbilityWheelWidget* AbilityWheelWidgetInstance;
	
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
 
	/* Unlock the Gun's input */
	void UnlockGunInput();

	void Test();

	bool bGunInputUnlocked = false;
};