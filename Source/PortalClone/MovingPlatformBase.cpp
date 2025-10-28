// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatformBase.h"

#include "FreezeComponent.h"
#include "RoundProgressBarWidget.h"
#include "Components/WidgetComponent.h"

// Sets default values
AMovingPlatformBase::AMovingPlatformBase()
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

void AMovingPlatformBase::BeginPlay() {

	Super::BeginPlay();

	if (WidgetComponent)
	{
		if (URoundProgressBarWidget* RoundProgressBarWidget = Cast<URoundProgressBarWidget>(WidgetComponent->GetUserWidgetObject()))
		{
			RoundProgressBarWidget->InitializeOwner(FreezeComponent);
		}
	}
}

void AMovingPlatformBase::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	if (FreezeComponent->IsFrozen())
		return;
	
	UpdateMovingPlatform(DeltaTime);
}

void AMovingPlatformBase::ApplyFreezeEffect_Implementation()
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

