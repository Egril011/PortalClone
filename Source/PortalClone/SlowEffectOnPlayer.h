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

private:
	float SavedRunningSpeed;
	float SavedWalkSpeed;
	FTimerHandle SlowTimer;
	TObjectPtr<APortalCloneCharacter> PlayerRef;
	
	//Restore the player's speed
	void RestorePlayerSpeed();
};
