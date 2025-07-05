// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameMode.h"
#include "MyGameInstance.h"
#include "PortalCloneCharacter.h"

void AMyGameMode::PlayerRespawn(AController* PlayerController) {

	if (!PlayerController)
		return;

	APawn* OldPlayer = PlayerController->GetPawn();

	if (OldPlayer) {

		OldPlayer->Destroy();
	}

	UGameInstance* GameInstance = GetGameInstance();

	UMyGameInstance* GI = Cast<UMyGameInstance>(GameInstance);

	if (GI) {

		//spawn the new player
		FActorSpawnParameters SpawnParam;
		SpawnParam.Owner = PlayerController;

		APawn* NewPlayer = GetWorld()->SpawnActor<APortalCloneCharacter>(
			DefaultPawnClass,
			GI->SpawnLocation,
			GI->SpawnRotation,
			SpawnParam
		);

		PlayerController->Possess(NewPlayer);
	}
}
