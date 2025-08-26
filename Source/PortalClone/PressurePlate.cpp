// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate.h"
#include "DoorPressedPlate.h"
#include "PressableInterface.h"
#include "RecallComponent.h"

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

	TogglePlate(false);
}

void APressurePlate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) {

	if (!OtherActor || OtherActor == this) {
		return;
	}

	/*Check if  the overlapping object implements the interface then change its colour and 
	then check if the door can open*/
	if (StaticMesh && ActivateColour && 
		OtherActor->GetClass()->ImplementsInterface(UPressableInterface::StaticClass()))
	{
		TogglePlate(true);
	}
}

void APressurePlate::OnOverlapEnd(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {

	if (!OtherActor || OtherActor == this) {
		return;
	}

	/*Check if the overlapping object implements the interface then change its colour and
	then close the door and disable the plate*/
	if (StaticMesh && NoActivateColour &&
		OtherActor->GetClass()->ImplementsInterface(UPressableInterface::StaticClass()))
	{
		if (auto* Recall = OtherActor->FindComponentByClass<URecallComponent>())
		{
			if (Recall->IsRecalling())
			{
				Recall->OnRecallFinished.AddUniqueDynamic(this, &APressurePlate::HandleRecallObject);
				return;
			}
		}
		TogglePlate(false);
	}
}

void APressurePlate::TogglePlate(bool bActivate)
{
	bIsActivate = bActivate;
	
	StaticMesh->SetMaterial(1, this->bIsActivate ? ActivateColour : NoActivateColour);

	if (DoorPressedPlate)
		DoorPressedPlate->ArePlateChanged();
}

void APressurePlate::HandleRecallObject()
{
	TogglePlate(false);
}
