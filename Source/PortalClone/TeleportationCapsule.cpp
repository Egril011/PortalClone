// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportationCapsule.h"

// Sets default values
ATeleportationCapsule::ATeleportationCapsule()
{
	// add the skeleton mesh to the root
	SkeletonMeshCapsule = CreateDefaultSubobject<USkeletalMeshComponent>
		(TEXT("SkeletonMeshCapsule"));
	RootComponent = SkeletonMeshCapsule;

	//Attach the Door to the capsule
	SkeletonMeshDoor = CreateDefaultSubobject<USkeletalMeshComponent>
		(TEXT("SkeletonMeshDoor"));

	SkeletonMeshDoor->SetupAttachment(SkeletonMeshCapsule);

	/*Attache the collider to the skeleton*/
	BoxCollisionPlayerDetection = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxColliderPlayerDetection"));
	BoxCollisionPlayerDetection->SetupAttachment(SkeletonMeshCapsule);

	BoxCollisionLeftWall = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxColliderLeftWall"));
	BoxCollisionLeftWall->SetupAttachment(SkeletonMeshCapsule);

	BoxCollisionRightWall = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxColliderRightWall"));
	BoxCollisionRightWall->SetupAttachment(SkeletonMeshCapsule);

	BoxCollisionBackWall = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxColliderBackWall"));
	BoxCollisionBackWall->SetupAttachment(SkeletonMeshCapsule);

	BoxCollisionTopWall = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxColliderTopWall"));
	BoxCollisionTopWall->SetupAttachment(SkeletonMeshCapsule);

	BoxCollisionPlayerDetection->OnComponentBeginOverlap.AddDynamic(this,
		&ATeleportationCapsule::OnOverlapBegin);

	//Attache the scene to the skeleton
	SceneTeleportation = CreateDefaultSubobject<USceneComponent>(
		TEXT("SceneTeleportation"));

	SceneTeleportation->SetupAttachment(SkeletonMeshCapsule);
}

//Interface implementation
void ATeleportationCapsule::Activate_Implementation() {

	OpenDoor();
}

void ATeleportationCapsule::OpenDoor() {

	if (!SkeletonMeshDoor->IsPlaying() && AnimOpenDoor) {

		SkeletonMeshDoor->PlayAnimation(AnimOpenDoor, false);

		SkeletonMeshDoor->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	//Reset the timer
	GetWorld()->GetTimerManager().ClearTimer(TimeHandleCloseDoor);

	//Start the delay to close the door after x sec
	GetWorld()->GetTimerManager().SetTimer(
		TimeHandleCloseDoor,
		this,
		&ATeleportationCapsule::CloseDoor,
		15.0f,
		false
	);
}

void ATeleportationCapsule::CloseDoor() {
	
	if (!SkeletonMeshCapsule->IsPlaying() && AnimCloseDoor) {

		SkeletonMeshCapsule->PlayAnimation(AnimCloseDoor, false);

		GetWorld()->GetTimerManager().ClearTimer(TimeHandleCloseDoor);
	}
}

void ATeleportationCapsule::OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) {

	if (!OtherActor || OtherActor == this) {
		return;
	}

	if (APortalCloneCharacter* Player = Cast<APortalCloneCharacter>(OtherActor))
	{
		PlayerTeleportation(Player);
	}
}

/*
* Get the scene component and with this, we gonna use its localisation to teleport the player
*/
void ATeleportationCapsule::PlayerTeleportation(APortalCloneCharacter* Player) {

	FVector Localisation = SceneTeleportation->GetComponentLocation();
	FRotator Rotator = SceneTeleportation->GetComponentRotation();

	Player->SetActorLocation(Localisation);
	Player->SetActorRotation(Rotator);
}

