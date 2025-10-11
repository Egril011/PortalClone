// Fill out your copyright notice in the Description page of Project Settings.


#include "SlowEffectOnPlayer.h"

#include "PortalCloneCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USlowEffectOnPlayer::USlowEffectOnPlayer()
{
}

void USlowEffectOnPlayer::SlowThePlayer(APortalCloneCharacter* PlayerCharacterRef, float percentage, int howMuchTimeSlow)
{
	if (!IsValid(PlayerCharacterRef))
		return;

	PlayerRef = PlayerCharacterRef;

	if (percentage < 0)
		return;
		
	//save the player's speed
	SavedRunningSpeed = PlayerCharacterRef->SprintSpeed;
	SavedWalkSpeed = PlayerCharacterRef->GetCharacterMovement()->MaxWalkSpeed;

	//Convent
	if (percentage >=1)
	{
		float newPercentage = FMath::Clamp(percentage/100, 0.0f, 1.0f);
		percentage = newPercentage;
	}

	//Set the new speed
	PlayerCharacterRef->GetCharacterMovement()->MaxWalkSpeed = (SavedWalkSpeed - (SavedWalkSpeed * percentage));
	PlayerCharacterRef->SprintSpeed = (SavedRunningSpeed - (SavedRunningSpeed * percentage));
	
	//Start the time for the player can restore its normal speed
	GetWorld()->GetTimerManager().ClearTimer(SlowTimer);
	GetWorld()->GetTimerManager().SetTimer(
		SlowTimer,
		this,
		&USlowEffectOnPlayer::RestorePlayerSpeed,
		howMuchTimeSlow,
		false);
}

void USlowEffectOnPlayer::RestorePlayerSpeed()
{
	if (!IsValid(PlayerRef))
		return;
	
	PlayerRef->SprintSpeed = SavedRunningSpeed;
	PlayerRef->GetCharacterMovement()->MaxWalkSpeed = SavedWalkSpeed;
	GetWorld()->GetTimerManager().ClearTimer(SlowTimer);
	PlayerRef = nullptr;
}