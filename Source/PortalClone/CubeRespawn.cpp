// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeRespawn.h"

// Sets default values
ACubeRespawn::ACubeRespawn()
{
	SpawnCubeLocalisation = CreateDefaultSubobject<USceneComponent>(TEXT("CubeSpawn"));
	RootComponent = SpawnCubeLocalisation;
}

void ACubeRespawn::BeginPlay() {

	Super::BeginPlay();

	//Initialize the location and rotation 
	Location = SpawnCubeLocalisation->GetRelativeLocation();
	Rotator = SpawnCubeLocalisation->GetRelativeRotation();
}

void ACubeRespawn::Respawn(UClass* Actor) {
	GetWorld()->SpawnActor<AActor>(Actor, Location, Rotator);
}
