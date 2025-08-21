// Fill out your copyright notice in the Description page of Project Settings.


#include "LightFlicker.h"

#include "LightFlickerComponent.h"
#include "Components/LightComponent.h"

// Sets default values
ALightFlicker::ALightFlicker() : Light(nullptr), LightFlickerComponent(nullptr)
{
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	RootComponent = SkeletalMeshComponent;
	
	LightFlickerComponent = CreateDefaultSubobject<ULightFlickerComponent>(TEXT("LightFlickerComponent"));
}

// Called when the game starts or when spawned
void ALightFlicker::BeginPlay()
{
	Super::BeginPlay();

	Light = FindComponentByClass<ULightComponent>();

	if (!Light)
	{
		UE_LOG(LogTemp,Warning,TEXT("ALightFlicker::FindComponentByClass Failed!"));
		return;
	}
	
	//Set its location at the same as SkeletalMesh
	Light->SetMobility(EComponentMobility::Movable);
	
	Light->SetWorldLocationAndRotation(SkeletalMeshComponent->GetComponentLocation(),
		SkeletalMeshComponent->GetComponentRotation());
}

