// Fill out your copyright notice in the Description page of Project Settings.


#include "UnlockGunAbilities.h"

#include "NotificationSubsystem.h"
#include "PortalCloneCharacter.h"
#include "PortalCloneGun.h"
#include "TrackGunStateComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AUnlockGunAbilities::AUnlockGunAbilities()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
}

void AUnlockGunAbilities::Interact_Implementation()
{
	if (ACharacter* Player = UGameplayStatics::GetPlayerCharacter(this, 0); Player != nullptr)
	{
		if (Player->IsA<APortalCloneCharacter>())
		{
			const APortalCloneCharacter* PortalPlayer = Cast<APortalCloneCharacter>(Player);

			if (!IsValid(PortalPlayer))
				return;

			if (!IsValid(PortalPlayer->EquippedGun))
				return;

			if (!PortalPlayer->EquippedGun->IsA<APortalCloneGun>())
				return;	

			UTrackGunStateComponent* TrackGunStateComponent = PortalPlayer->EquippedGun->GetTrackGunStateComponent();

			if (!IsValid(TrackGunStateComponent))
				return;

			for (const auto UnlockAbility : GunStateHandlers)
			{
				switch (UnlockAbility)
				{
				case EGunStateHandler::Freeze:
					if (!TrackGunStateComponent->CanFreezeObject())
					{
						TrackGunStateComponent->UnlockFreezeObject();

						//Message to say he has unlocked the freeze ability
						if (UNotificationSubsystem* NotificationSubsystem = UNotificationSubsystem::NotificationSubsystemGetWord(this))
						{
							NotificationSubsystem->ShowNotification("You have unlocked the Freeze ability. \n"
											   "Now, you can press 'Q' to use the ability"
											   " and freeze an object for a limited time.");
						}
					}
					break;

				case EGunStateHandler::Grab:
					if (!TrackGunStateComponent->CanGrabObject())
					{
						TrackGunStateComponent->UnlockGrabObject();
						
						//Message to say he has unlocked the grab ability
						if (UNotificationSubsystem* NotificationSubsystem = UNotificationSubsystem::NotificationSubsystemGetWord(this))
						{
							NotificationSubsystem->ShowNotification("You have unlocked the Grab ability. \n"
											   "Now, you can press 'Q' to use the ability"
											   " and grab an object to move it.");
						}
					}
					break;

				case EGunStateHandler::Recall:
					if (!TrackGunStateComponent->CanRecallObject())
					{
						TrackGunStateComponent->UnlockRecallObject();

						//Message to say he has unlocked the recall ability
						if (UNotificationSubsystem* NotificationSubsystem = UNotificationSubsystem::NotificationSubsystemGetWord(this))
						{
							NotificationSubsystem->ShowNotification("You have unlocked the Recall ability. \n"
											   "Now, you can press 'Q' to choose the ability"
											   " and recall an moved object.");
						}
					}
					break;
					
				default:
					break;
				}
			}
		}
	}

	Destroy();
}


