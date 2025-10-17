// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatformNormal.h"

#include "Math/UnitConversion.h"

void AMovingPlatformNormal::BeginPlay()
{
	Super::BeginPlay();

	bPointAOrB = false;
	StartLocation = StartPoint->GetComponentLocation();
	EndLocation = EndPoint->GetComponentLocation();
	TargetLocation = bPointAOrB ? StartLocation : EndLocation;
}

void AMovingPlatformNormal::UpdateMovingPlatform(float DeltaTime)
{
	//Move the platform
	FVector ToTarget = TargetLocation - GetActorLocation();
	FVector Direction = ToTarget.GetSafeNormal();
	FVector NewActorLocation = GetActorLocation() + (Direction * MoveSpeed * DeltaTime);
	SetActorLocation(NewActorLocation);

	if (FVector::Dist(NewActorLocation, TargetLocation) < 1.f)
	{
		bPointAOrB = !bPointAOrB;
		TargetLocation = bPointAOrB ? StartLocation : EndLocation;
	}
}
