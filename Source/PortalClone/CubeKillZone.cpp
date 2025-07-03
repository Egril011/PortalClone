// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeKillZone.h"
#include "PortalCloneWeaponComponent.h"
#include "PressableInterface.h"

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

		//Search if the player grab an object 
		for (TObjectIterator<UPhysicsHandleComponent> IT; IT; ++IT) {

			UPhysicsHandleComponent* Handle = *IT;

			if (Handle->GrabbedComponent == OtherComp) {
				Handle->ReleaseComponent();

				//Disable the velocity
				if (OtherComp && OtherComp->IsSimulatingPhysics()) {
					OtherComp->SetPhysicsLinearVelocity(FVector::ZeroVector);
					OtherComp->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
				}
				break;
			}
		}

		OtherActor->SetActorHiddenInGame(true);
		OtherActor->SetActorEnableCollision(false);
		OtherActor->SetActorTickEnabled(true);

		CubeRespawn->SpawnActor();
	}
}