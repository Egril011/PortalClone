// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "InputAction.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "PortalCloneWeaponComponent.generated.h"

class APortalCloneCharacter;
class UTrackGunAbility;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTALCLONE_API UPortalCloneWeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:

	UPortalCloneWeaponComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FireEffectAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ChangeGunStateAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* GrabObjectAction;
	
	//To get the Muzzle'name from the gun's skeleton 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName MuzzleSocketName = TEXT("Muzzle");

protected:
	/** Ends gameplay for this component. */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle;

private:
	/** The Character holding this weapon*/
	APortalCloneCharacter* Character;

	UPROPERTY()
	UTrackGunAbility* GunAbilities;

	UPROPERTY()
	UPrimitiveComponent* Primitive;

	UPROPERTY()
	USceneComponent* MuzzleSceneGrabbedObject;

	//method to grab item
	UFUNCTION(BlueprintCallable, Category = "PortalWeapon")
	void GrabObject();

	//method to throw the object
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ThrowObject();
	
	//method to shot the effect
	UFUNCTION(BlueprintCallable, Category = "PortalWeapon")
	void FireEffect();

	//method to change the gun state
	UFUNCTION(BlueprintCallable, Category = "PortalWeapon")
	void ChangeGunEffect();

	//method to drop the object
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void DropObject();


};
