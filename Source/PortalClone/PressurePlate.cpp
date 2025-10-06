// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate.h"
#include "DoorPressedPlate.h"
#include "PortalCloneCharacter.h"
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

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &APressurePlate::OnOverlapBegin);

	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &APressurePlate::OnOverlapEnd);
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

	//See if the OtherActor can Trigger the pressure plate
	if (!CanTriggerBy(OtherActor))
		return;

	if (StaticMesh && DoorPressedPlate && ActivateColour && !IsActivate()) {
		TogglePlate(true);
	} 
}

void APressurePlate::OnOverlapEnd(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {

	if (!OtherActor || OtherActor == this) {
		return;
	}
	
	//See if the OtherActor can OverlapEnd the pressure plate
	if (!CanTriggerBy(OtherActor))
		return;

	if (!StaticMesh && !DoorPressedPlate && !ActivateColour && !bIsActivate)
		return;

	//Find the URecallComponent to handle if the object is recalling
	RecallComponent = OtherActor->FindComponentByClass<URecallComponent>();
	
	if (IsValid(RecallComponent) && RecallComponent->IsRecalling())
	{
		RecallComponent->OnRecallFinished.AddUniqueDynamic(this, &APressurePlate::APressurePlate::HandleRecallObject);
		return;
	}
	
	TogglePlate(false);
}

void APressurePlate::TogglePlate(bool bActivate)
{
	bIsActivate = bActivate;
	
	StaticMesh->SetMaterial(1, this->bIsActivate ? ActivateColour : NoActivateColour);

	if (DoorPressedPlate)
		DoorPressedPlate->ArePlateChanged();
}

bool APressurePlate::CanTriggerBy(AActor* Actor) const
{
	bool bIsPlayer = Actor->IsA<APortalCloneCharacter>();
	bool bIsObject = Actor->Implements<UPressableInterface>();

	switch (TriggerType)
	{
	case EPressurePlateTriggerType::PlayerOnly:
		return bIsPlayer && !bIsObject;

	case EPressurePlateTriggerType::ObjectOnly:
		return bIsObject && !bIsPlayer;

	case EPressurePlateTriggerType::Any:
		return bIsPlayer || bIsObject;

	default:
		return false;
	}
}

void APressurePlate::HandleRecallObject()
{
	RecallComponent->OnRecallFinished.RemoveDynamic(this, &APressurePlate::HandleRecallObject);
	RecallComponent = nullptr;

	if (StaticMesh && DoorPressedPlate && NoActivateColour && bIsActivate)
		TogglePlate(false);
}
