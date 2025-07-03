// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GunFireComponent.generated.h"

class APortalCloneGun;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTALCLONE_API UGunFireComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGunFireComponent();


private: 
	APortalCloneGun* GunRef;

	//method to shot the effect
	void FireEffect();

	//Initalize the GunRef
	void InitializeComponent();  
};
