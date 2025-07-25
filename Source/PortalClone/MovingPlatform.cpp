// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	RootComponent = SkeletalMesh;

	StartPoint = CreateDefaultSubobject<USceneComponent>(TEXT("StartPoint"));
	StartPoint->SetupAttachment(RootComponent);

	EndPoint = CreateDefaultSubobject<USceneComponent>(TEXT("EndPoint"));
	EndPoint->SetupAttachment(RootComponent);
}

void AMovingPlatform::BeginPlay() {

	Super::BeginPlay();

	StartLocation = StartPoint->GetComponentLocation();
	EndLocation = EndPoint->GetComponentLocation();
}

void AMovingPlatform::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	if (bIsWaiting)
	{
		CurrentWaitTime -= DeltaTime;
		if (CurrentWaitTime <= 0.0f)
		{
			bIsWaiting = false;
		}
		return;
	}


	FVector CurrentLocation = GetActorLocation();
	FVector Destination = bMovingToTarget ? StartLocation : EndLocation;

	FVector Direction = (Destination - CurrentLocation).GetSafeNormal();
	FVector NewLocation = CurrentLocation + Direction * MoveSpeed * DeltaTime;

	SetActorLocation(NewLocation);

	if (FVector::Dist(NewLocation, Destination) < 1.0f) {

		bMovingToTarget = !bMovingToTarget;
		bIsWaiting = true;
		CurrentWaitTime = WaitTime;
	}
}

