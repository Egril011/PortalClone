// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalCube.h"

#include "RecallComponent.h"

// Sets default values
ANormalCube::ANormalCube()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	//Create the component
	RecallComponent = CreateDefaultSubobject<URecallComponent>(TEXT("RecallComponent"));
}

void ANormalCube::BeginPlay() {

	Super::BeginPlay();
	StaticMesh->SetSimulatePhysics(true);
}

void ANormalCube::OnPlatePressed_Implementation() {

}

void ANormalCube::Recallable_Implementation()
{
	if (!RecallComponent)
		return;
	RecallComponent->StartRecall();
}
