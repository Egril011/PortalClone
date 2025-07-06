// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GunGrabComponent.generated.h"

class APortalCloneGun;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTALCLONE_API UGunGrabComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGunGrabComponent();

	//method to grab an object
	void GrabObject();

	//method to throw the object
	void ThrowObject();

	virtual void TickComponent(float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction*
		ThisTickFunction) override;

	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle;

protected: 
	virtual void BeginPlay() override;

private :
	UPROPERTY()
	APortalCloneGun* GunRef;

	UPrimitiveComponent* Primitive;

	//method to drop the object
	void DropObject();
};
