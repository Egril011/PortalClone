// Fill out your copyright notice in the Description page of Project Settings.


#include "UnlockGunAbilities.h"

#include "PortalCloneCharacter.h"
#include "PortalCloneGun.h"
#include "TrackGunStateComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AUnlockGunAbilities::AUnlockGunAbilities()
{
}

void AUnlockGunAbilities::Interact_Implementation()
{
	if (ACharacter* Player = UGameplayStatics::GetPlayerCharacter(this, 0); Player != nullptr)
	{
		if (Player->IsA<APortalCloneCharacter>())
		{
			const APortalCloneCharacter* PortalPlayer = Cast<APortalCloneCharacter>(Player);

			if (!PortalPlayer)
				return;

			if (!PortalPlayer->EquippedGun)
				return;

			if (!PortalPlayer->EquippedGun->IsA<APortalCloneGun>())
				return;	

			UTrackGunStateComponent* TrackGunStateComponent = PortalPlayer->EquippedGun->TrackGunAbility;

			if (!TrackGunStateComponent)
				return;

			for (const auto UnlockAbility : GunStateHandlers)
			{
				switch (UnlockAbility)
				{
				case EGunStateHandler::Freeze:
					TrackGunStateComponent->UnlockFreezeObject();
					break;

				case EGunStateHandler::Grab:
					TrackGunStateComponent->UnlockGrabObject();
					break;

				case EGunStateHandler::Recall:
					TrackGunStateComponent->UnlockRecallObject();
					break;
					
				default:
					break;
				}
			}
		}
	}
}


