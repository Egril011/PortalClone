// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

#include "FreezeComponent.h"
#include "RoundProgressBarWidget.h"
#include "Components/WidgetComponent.h"

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

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(SkeletalMesh);

	FreezeComponent = CreateDefaultSubobject<UFreezeComponent>(TEXT("FreezeComponent"));
}

void AMovingPlatform::BeginPlay() {

	Super::BeginPlay();

	StartLocation = StartPoint->GetComponentLocation();
	EndLocation = EndPoint->GetComponentLocation();

	if (WidgetComponent)
	{
		if (URoundProgressBarWidget* RoundProgressBarWidget = Cast<URoundProgressBarWidget>(WidgetComponent->GetUserWidgetObject()))
		{
			RoundProgressBarWidget->InitializeOwner(FreezeComponent);
		}
	}
}

void AMovingPlatform::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	if (IsValid(FreezeComponent) && FreezeComponent->IsFrozen())
	{
		return;
	}
	
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

void AMovingPlatform::ApplyFreezeEffect_Implementation()
{
	if (!FreezeComponent)
		return;

	if (FreezeComponent->IsFrozen())
	{
		WidgetComponent->SetVisibility(false);
		FreezeComponent->CancelFreezeEffect();
		return;
	}
	WidgetComponent->SetVisibility(true);
	FreezeComponent->StartFreezeEffect();
}

