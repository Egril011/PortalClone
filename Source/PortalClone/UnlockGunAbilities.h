// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EGunStateHandler.h"
#include "InteractableInterface.h"
#include "GameFramework/Actor.h"
#include "UnlockGunAbilities.generated.h"


UCLASS()
class PORTALCLONE_API AUnlockGunAbilities : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnlockGunAbilities();

protected:
	//The list to unlock abilities 
	UPROPERTY(EditAnywhere, Category= "Ability")
	TArray<EGunStateHandler> GunStateHandlers;

private:
	virtual void Interact_Implementation() override;
};
