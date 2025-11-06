// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameMode.h"
#include "MyGameInstance.h"
#include "PortalCloneCharacter.h"
#include "PortalCloneGun.h"
#include "Engine/GameViewportClient.h"

void AMyGameMode::PlayerRespawn(AController* PlayerController) {

	if (!PlayerController)
		return;
	
	APawn* OldPlayer = PlayerController->GetPawn();

	if (OldPlayer) {
		//Save the gun to respawn
		if (APortalCloneCharacter* OldPlayerCharacter = Cast<APortalCloneCharacter>(OldPlayer))
		{
			if (OldPlayerCharacter->EquippedGun)
			{
				GunToRespawn = OldPlayerCharacter->EquippedGun->GetClass();
				OldPlayerCharacter->EquippedGun->Destroy();
			}
		}
		
		OldPlayer->Destroy();
	}

	UGameInstance* GameInstance = GetGameInstance();

	UMyGameInstance* GI = Cast<UMyGameInstance>(GameInstance);

	if (GI) {

		//spawn the new player
		FActorSpawnParameters SpawnParam;
		SpawnParam.Owner = PlayerController;

		APortalCloneCharacter* NewPlayer = GetWorld()->SpawnActor<APortalCloneCharacter>(
			DefaultPawnClass,
			GI->SpawnLocation,
			GI->SpawnRotation,
			SpawnParam
		);

		PlayerController->Possess(NewPlayer);

		//Respawn the Gun
		FActorSpawnParameters SpawnParamGun;
		SpawnParamGun.Owner = NewPlayer;
		
		if (IsValid(GunToRespawn) && IsValid(NewPlayer))
		{
			APortalCloneGun* NewGun = NewPlayer->GetWorld()->SpawnActor<APortalCloneGun>(
			GunToRespawn,
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			SpawnParamGun);

			//Attach the gun to the player
			if (!IsValid(NewGun))
				return;

			NewGun->AttachWeapon(NewPlayer);
			NewPlayer->EquippedGun = NewGun;
		}
	}
}
