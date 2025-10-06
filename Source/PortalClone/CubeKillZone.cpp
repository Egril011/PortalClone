// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeKillZone.h"

#include "GunGrabComponent.h"
#include "PressableInterface.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values
ACubeKillZone::ACubeKillZone()
{
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	RootComponent = BoxCollider;

	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ACubeKillZone::OnOverlapBegin);
}

void ACubeKillZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) {

	if (OtherActor->GetClass()->ImplementsInterface(UPressableInterface::StaticClass())) {
		
		//Check if the otherActor is currently grabbed
		if (UGunGrabComponent::ActiveGrabber.IsValid()) {
			UGunGrabComponent::ActiveGrabber->ForceStopGrabIfHoldingObject(OtherComp);
		}

		OtherActor->SetActorHiddenInGame(true);
		OtherActor->SetActorEnableCollision(false);
		OtherActor->SetActorTickEnabled(false);
		
		CubeRespawn->SpawnActor();
	}
}