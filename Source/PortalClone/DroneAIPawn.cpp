// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneAIPawn.h"

#include "DroneAIController.h"
#include "LaserComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
ADroneAIPawn::ADroneAIPawn() : DroneAIMesh(nullptr)
{
	PrimaryActorTick.bCanEverTick = false;

	DroneAIMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Drone_Mesh"));
	RootComponent = DroneAIMesh;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Drone_Box"));
	BoxComponent->SetupAttachment(DroneAIMesh);
	
	//Allow the Drone to move in X/Y/Z
	DroneMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Drone_Movement"));
	DroneMovement->UpdatedComponent = DroneAIMesh;
	
	//Use the Drone Controller for this class
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ADroneAIController::StaticClass();
	bUseControllerRotationPitch = true;
}

void ADroneAIPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (LaserComponent)
	{
		CurrentLaser = NewObject<ULaserComponent>(this, LaserComponent);
		CurrentLaser->RegisterComponent();
	}
}

// Called to bind functionality to input
void ADroneAIPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

TObjectPtr<ULaserComponent> ADroneAIPawn::GetCurrentLaserComponent() const
{
	return CurrentLaser;
}

