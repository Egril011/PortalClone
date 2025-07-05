// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerKillZone.h"
#include "PortalCloneCharacter.h"
#include "MyGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerKillZone::APlayerKillZone()
{
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	RootComponent = BoxCollider;

	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &APlayerKillZone::OnOverlapBegin);
}

void APlayerKillZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) {

	if (OtherActor && OtherActor != this) {

		if (OtherActor->IsA(APortalCloneCharacter::StaticClass())) {

			APortalCloneCharacter* Player = Cast<APortalCloneCharacter>(OtherActor);

			AController* Controller = Player->GetController();

			AMyGameMode* GM = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
			
			if (GM) {
				GM->PlayerRespawn(Controller);
			}
		}
	}
}
