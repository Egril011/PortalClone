// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate.h"

// Sets default values
APressurePlate::APressurePlate()
{
	//add the static mesh to the root
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	/**Add the collider**/
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollision->SetupAttachment(StaticMesh);

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, 
		&APressurePlate::OnOverlapBegin);

	BoxCollision->OnComponentEndOverlap.AddDynamic(this, 
		&APressurePlate::OnOverlapEnd);
}

void APressurePlate::BeginPlay() {

	Super::BeginPlay();

	StaticMesh->SetMaterial(1, NoActivateColour);
}

void APressurePlate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) {

	if (!OtherActor || OtherActor == this) {
		return;
	}

	if (StaticMesh && ActivateColour)
	{
		StaticMesh->SetMaterial(1, ActivateColour);
	}
}

void APressurePlate::OnOverlapEnd(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {

	if (!OtherActor || OtherActor == this) {
		return;
	}

	// Example logic
	if (StaticMesh && NoActivateColour)
	{
		StaticMesh->SetMaterial(1, NoActivateColour);
	}
}
