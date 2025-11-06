// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeRespawn.h"

#include "NormalCube.h"

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

	//Initialize the pool
	InitializePool();
	SpawnActor();
	
}

AActor* ACubeRespawn::SpawnActor() {
	
	for (AActor* Actor : ActorList) {
		
		if (Actor && Actor->IsHidden()) {
			
			Actor->SetActorLocation(Location);
			Actor->SetActorRotation(Rotator);

			//Set the Velocity to 0
			if (UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(Actor->GetRootComponent()))
			{
				PrimitiveComponent->SetPhysicsLinearVelocity(FVector::ZeroVector);
			}
			
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
		
		//Spawn the Actor 
		AActor* Actor = GetWorld()->SpawnActor<AActor>(Target, FVector::ZeroVector, FRotator::ZeroRotator);
		if (Actor) {
			
			Actor->SetActorHiddenInGame(true);
			Actor->SetActorEnableCollision(false);
			Actor->SetActorTickEnabled(false);

			//if the Actor is a normalcube, save the reference to the respawn
			if (ANormalCube* Cube = Cast<ANormalCube>(Actor))
				Cube->Respawn = this;

			ActorList.Add(Actor);
		}
	}
}