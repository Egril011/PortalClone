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
	Location = SpawnCubeLocalisation->GetComponentLocation();
	Rotator = SpawnCubeLocalisation->GetComponentRotation();

	//Initalize the pool
	InitializePool();
	SpawnActor();
	
}

AActor* ACubeRespawn::SpawnActor() {
	
	for (AActor* Actor : ActorList) {
		
		if (Actor && Actor->IsHidden()) {
			
			Actor->SetActorLocation(Location);
			Actor->SetActorRotation(Rotator);

			Actor->SetActorHiddenInGame(false);
			Actor->SetActorEnableCollision(true);
			Actor->SetActorTickEnabled(true);

			return Actor;
		}
	}

	return nullptr;
}

void ACubeRespawn::InitializePool() {

	if (!Target)
		return;

	for (int i = 0; i < ListSize; i++) {
		
		AActor* Actor = GetWorld()->SpawnActor<AActor>(Target, FVector::ZeroVector, FRotator::ZeroRotator);
		if (Actor) {

			Actor->SetActorHiddenInGame(true);
			Actor->SetActorEnableCollision(false);
			Actor->SetActorTickEnabled(false);

			ActorList.Add(Actor);
		}
	}
}