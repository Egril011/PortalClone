// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalCube.h"

// Sets default values
ANormalCube::ANormalCube()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
}

void ANormalCube::BeginPlay() {

	Super::BeginPlay();

	StaticMesh->SetSimulatePhysics(true);
}

void ANormalCube::OnPlatePressed_Implementation() {

}
