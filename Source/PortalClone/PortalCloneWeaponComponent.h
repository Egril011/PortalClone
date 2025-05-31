// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "InputAction.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "PortalCloneWeaponComponent.generated.h"

class APortalCloneCharacter;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTALCLONE_API UPortalCloneWeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class APortalCloneProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector MuzzleOffset;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;


	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	bool AttachWeapon(APortalCloneCharacter* TargetCharacter);

	//method to shot the effect
	UFUNCTION(BlueprintCallable, Category = "PortalWeapon")
	void FireEffect();

	//method to change the gun state
	UFUNCTION(BlueprintCallable, Category = "PortalWeapon")
	void ChangeGunEffect();

	//method to grab item
	UFUNCTION(BlueprintCallable, Category = "PortalWeapon")
	void GrabItem();

	//method to Drop item
	UFUNCTION(BlueprintCallable, Category = "PortalWeapon")
	void DropItem();

	//The Input to shot
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FireEffectAction;

	//The input to change the gun's state
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ChangeGunStateAction;

	//The input to grab an item causes the item to move in front of the player.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* GrabItemAction;
	
	//To get the Muzzle from the gun's skeleton 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName MuzzleSocketName = TEXT("Muzzle");

protected:
	/** Ends gameplay for this component. */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	/** The Character holding this weapon*/
	APortalCloneCharacter* Character;

	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle;
};
