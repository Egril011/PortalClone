// Fill out your copyright notice in the Description page of Project Settings.


#include "ColliderEndGame.h"

#include "PortalCloneCharacter.h"
#include "VictoryWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AColliderEndGame::AColliderEndGame()
{
	BoxColliderEndGame = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxColliderEndGame"));
	RootComponent = BoxColliderEndGame;

	if (BoxColliderEndGame)
		BoxColliderEndGame->OnComponentBeginOverlap.AddUniqueDynamic(this, &AColliderEndGame::OnOverlapBegin);
}

void AColliderEndGame::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this)
		return;

	if (OtherActor->IsA<APortalCloneCharacter>())
	{
		ACharacter* Character = Cast<ACharacter>(OtherActor);
		if (!IsValid(Character))
			return;

		APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
		UVictoryWidget* VictoryWidget = CreateWidget<UVictoryWidget>(PlayerController, EndWidget);
		if (!IsValid(VictoryWidget))
			return;

		VictoryWidget->AddToViewport();
	}
}

