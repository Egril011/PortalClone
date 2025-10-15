// Fill out your copyright notice in the Description page of Project Settings.


#include "SlowEffectOnPlayer.h"

#include "EngineUtils.h"
#include "PortalCloneCharacter.h"
#include "Engine/PostProcessVolume.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values for this component's properties
USlowEffectOnPlayer::USlowEffectOnPlayer()
{
}

void USlowEffectOnPlayer::SlowThePlayer(APortalCloneCharacter* PlayerCharacterRef, float percentage, int howMuchTimeSlow)
{
	bisSlowing = true;
	
	if (!IsValid(PlayerCharacterRef))
		return;

	PlayerRef = PlayerCharacterRef;

	//Apply the vignette
	ApplyVignette();

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
	bisSlowing = false;
}

void USlowEffectOnPlayer::ApplyVignette()
{
	if (!IsValid(PlayerRef))
		return;

	//Get the postProcessing in the level and set the Vignette to 1
	for (TActorIterator<APostProcessVolume> ActorIterator(PlayerRef->GetWorld()); ActorIterator; ++ActorIterator)
	{
		PostProcessVolume = Cast<APostProcessVolume>(*ActorIterator);
		if (!IsValid(PostProcessVolume) || !PostProcessVolume->bUnbound)
			return;

		FPostProcessSettings& Settings = PostProcessVolume->Settings;
		if (Settings.WeightedBlendables.Array.Num() > 0)
		{
			Settings.WeightedBlendables.Array[0].Weight = 1.0f;
			VignetteIntensity = 1.0f;
			
			//Start the time to decrease the vignette
			GetWorld()->GetTimerManager().ClearTimer(VignetteTimer);
			GetWorld()->GetTimerManager().SetTimer(
				VignetteTimer,
				this,
				&USlowEffectOnPlayer::DecreaseVignette,
				0.05f,
				true);
		}
			break;
	}
}

void USlowEffectOnPlayer::DecreaseVignette()
{
	if (!PostProcessVolume)
		return;
	
	FPostProcessSettings& Settings = PostProcessVolume->Settings;
	if (Settings.WeightedBlendables.Array.Num() > 0)
	{
		VignetteIntensity -= 0.01;
		if (VignetteIntensity <= 0)
			RemoveVignette();
		
		VignetteIntensity = FMath::Clamp(VignetteIntensity, 0.0f, 1.0f);
		Settings.WeightedBlendables.Array[0].Weight = VignetteIntensity;
	}
}

void USlowEffectOnPlayer::RemoveVignette()
{
	GetWorld()->GetTimerManager().ClearTimer(VignetteTimer);
	PostProcessVolume = nullptr;
}
