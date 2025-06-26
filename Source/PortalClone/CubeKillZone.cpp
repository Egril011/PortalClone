// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeKillZone.h"
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

		CubeRespawn->Respawn(OtherActor->GetClass());
		OtherActor->Destroy();
	}
}