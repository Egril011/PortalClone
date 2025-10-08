// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InputAction.h"
#include "PortalCloneCharacter.h"
#include "Components/SphereComponent.h"
#include "Delegates/Delegate.h"
#include "PortalCloneGun.generated.h"

class UGunWidgetComponent;
class UGunFreezeComponent;
class UGunRecallComponent;
class UTrackGunStateComponent;
class UGunFireComponent;
class UGunGrabComponent;
class UGunVFXComponent;
class UAbilityWheelComponent;
class UAbilityWheelWidget;

UCLASS()
class PORTALCLONE_API APortalCloneGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortalCloneGun();

	//Give a pointer to the character 
	APortalCloneCharacter* GetCharacter() const {return Character.Get() ;};

	//Get the muzzleName
	FName GetMuzzleSocketName() const { return MuzzleSocketName; }

	//Getter
	UGunGrabComponent* GetGrabComponent() const {return GunGrabComponent; }
	UGunRecallComponent* GetRecallComponent() const {return GunRecallComponent; }
	UGunFreezeComponent* GetFreezeComponent() const {return GunFreezeComponent; }
	UTrackGunStateComponent* GetTrackGunStateComponent() const {return TrackGunAbility; }
	USkeletalMeshComponent* GetMesh() const {return GunSkeletalMesh; }
	
	/** Attaches the actor to a FirstPersonCharacter */
	void AttachWeapon(APortalCloneCharacter* TargetCharacter);
	
	/*BroadCast*/
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnShootVFX, FName, VFXName, FVector, TargetLocation);
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnShootVFX OnShootVFX;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndShootVFX);
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnEndShootVFX OnEndShootVFX;

protected:
	//Skeleton
	UPROPERTY(EditAnyWhere)
	USkeletalMeshComponent* GunSkeletalMesh;

	/** MappingContext and Inputs*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ChangeGunStateAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* HandleMouseRightInput;
	
	/*Gun Components*/
	UPROPERTY(EditAnywhere, Category = "GunComponent")
	UTrackGunStateComponent* TrackGunAbility;

	UPROPERTY(EditAnywhere, Category = "GunComponent")
	UGunFireComponent* GunFireComponent;

	UPROPERTY(EditAnywhere, Category = "GunComponent")
	UGunGrabComponent* GunGrabComponent;

	UPROPERTY(EditAnywhere, Category = "GunComponent")
	UGunRecallComponent* GunRecallComponent;

	UPROPERTY(EditAnywhere, Category = "GunComponent")
	UGunVFXComponent* GunVFXComponent;

	UPROPERTY(EditAnywhere, Category = "GunComponent")
	UAbilityWheelComponent* AbilityWheelComponent;

	UPROPERTY(EditAnywhere, Category="GunComponent")
	TObjectPtr<UGunFreezeComponent> GunFreezeComponent;

	UPROPERTY(EditAnywhere, Category="GunComponent")
	TObjectPtr<UGunWidgetComponent> GunWidgetComponent;

	//Collider
	UPROPERTY()
	USphereComponent* SphereCollider;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	//method
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	/** The Character holding this weapon*/
	UPROPERTY()
	TObjectPtr<APortalCloneCharacter> Character;

	//To get the Muzzle's name from the gun's skeleton 
	UPROPERTY(EditAnywhere, Category = "Weapon")
	FName MuzzleSocketName = TEXT("Muzzle");

	/* Unlock the Gun's input */
	void UnlockGunInput();
	
	bool bGunInputUnlocked = false;
};