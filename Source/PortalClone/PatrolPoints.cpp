// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolPoints.h"

#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"

// Sets default values for this component's properties
APatrolPoints::APatrolPoints()
{
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(SphereComponent);
}

