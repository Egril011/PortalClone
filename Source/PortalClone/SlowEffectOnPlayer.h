// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SlowEffectOnPlayer.generated.h"


class APortalCloneCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTALCLONE_API USlowEffectOnPlayer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USlowEffectOnPlayer();

	//Set the new player's speed based on the percentage 
	void SlowThePlayer(APortalCloneCharacter* PlayerCharacter, float percentage, int howMuchTimeSlow);

	//Check if the player has already been slowed
	bool GetIsSlowing() const {return bisSlowing;};

	float GetPercentageOfSlow() const {return PercentageOfSlow;};
	float GetSlowEffectDuration() const {return SlowEffectDuration;};

private:
	float SavedRunningSpeed;
	float SavedWalkSpeed;
	float VignetteIntensity;
	bool bisSlowing;
	FTimerHandle SlowTimer;
	FTimerHandle VignetteTimer;
	TObjectPtr<APortalCloneCharacter> PlayerRef;
	TObjectPtr<APostProcessVolume> PostProcessVolume;

	UPROPERTY(EditAnywhere, Category="SlowEffectOnplayer|Variable", meta=(AllowPrivateAccess))
	float PercentageOfSlow = 0.5f;

	UPROPERTY(EditAnywhere, Category="SlowEffectOnplayer|Variable", meta=(AllowPrivateAccess))
	float SlowEffectDuration = 5.f;
	
	//Restore the player's speed
	void RestorePlayerSpeed();

	//Apply the Vignette effect
	void ApplyVignette();

	//Decrease the Vignette intensity
	void DecreaseVignette();

	//Remove the vignette effect
	void RemoveVignette();
};
