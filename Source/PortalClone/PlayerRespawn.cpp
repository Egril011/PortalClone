// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerRespawn.h"
#include "MyGameInstance.h"
#include "PortalCloneCharacter.h"

// Sets default values
APlayerRespawn::APlayerRespawn() {

	SceneSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("SceneSpawn"));
	RootComponent = SceneSpawn;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(SceneSpawn);

	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, 
		&APlayerRespawn::OnOverlapBegin);
} 

void APlayerRespawn::BeginPlay() {

	Super::BeginPlay();

	SpawnLocation_ = SceneSpawn->GetComponentLocation();
	SpawnRotation_ = SceneSpawn->GetComponentRotation();
}

void APlayerRespawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) {

	if (OtherActor != this && OtherActor) {

		/*Cast to the player then get the Game Instance to modify its variables*/
		if (OtherActor->IsA(APortalCloneCharacter::StaticClass())) {

			UGameInstance* GameInstance = GetGameInstance();

			UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GameInstance);

			if (MyGameInstance) {
				
				MyGameInstance->SpawnLocation = SpawnLocation_;
				MyGameInstance->SpawnRotation = SpawnRotation_;
			}
		}
	}

}