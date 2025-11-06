// Fill out your copyright notice in the Description page of Project Settings.
#include "DoorPressedPlate.h"

#include "MyGameInstance.h"
#include "MyGameMode.h"
#include "PortalCloneCharacter.h"
#include "PressurePlate.h"

// Sets default values  
ADoorPressedPlate::ADoorPressedPlate()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	RootComponent = SkeletalMesh;

	BoxComponentRightSide = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponentRightSide"));
	BoxComponentRightSide->SetupAttachment(SkeletalMesh);

	BoxComponentLeftSide = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponentLeftSide"));
	BoxComponentLeftSide->SetupAttachment(SkeletalMesh);

	BoxComponentFront = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponentFront"));
	BoxComponentFront->SetupAttachment(SkeletalMesh);

	BoxComponentKillZone = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponentKillZone"));
	BoxComponentKillZone->SetupAttachment(SkeletalMesh);

	if (BoxComponentKillZone)
		BoxComponentKillZone->OnComponentBeginOverlap.AddUniqueDynamic(this, &ADoorPressedPlate::KillPlayer);

	DoorState = EDoorAnimation::Close;
}

void ADoorPressedPlate::ArePlateChanged() {

	if (AreAllPlatesActivated()) {
		PlayOpenDoor();
	}
	else {
		PlayCloseDoor();
	}
}

bool ADoorPressedPlate::AreAllPlatesActivated() const {

	if (DoorActivationMode == EDoorActivationMode::AllPressurePlates )
	{
		for (APressurePlate* Plate : RequiredPressurePlate) {
			
			if (!Plate->IsActivate())
				return false;
		}
		return true;
	}
	
	else if (DoorActivationMode == EDoorActivationMode::AnyPressurePlates)
	{
		for (APressurePlate* Plate : RequiredPressurePlate)
		{
			if (Plate->IsActivate())
			{
				return true;
			}
		}
		return false;
	}
	return false;
}

void ADoorPressedPlate::PlayOpenDoor() {

	if (SkeletalMesh && DoorState == EDoorAnimation::Close) {
		
		SkeletalMesh->PlayAnimation(OpenDoorAnimation, false);
		BoxComponentFront->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		BoxComponentKillZone->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		DoorState = EDoorAnimation::Open;
	}
}

void ADoorPressedPlate::PlayCloseDoor() {

	if(SkeletalMesh && DoorState == EDoorAnimation::Open){
	
		SkeletalMesh->PlayAnimation(CloseDoorAnimation, false);
		BoxComponentFront->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		BoxComponentKillZone->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		DoorState = EDoorAnimation::Close;
	}
}

void ADoorPressedPlate::KillPlayer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if the player touches the kill zone respawn it 
	if (OtherActor == this)
		return;

	if (OtherActor && OtherActor->IsA<APortalCloneCharacter>())
	{
		AMyGameMode* GameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
		if (!IsValid(GameMode))
			return;

		if (ACharacter* Character = Cast<ACharacter>(OtherActor))
		{
			if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
			{
				GameMode->PlayerRespawn(PlayerController);
			}
		}
	}
}