// Fill out your copyright notice in the Description page of Project Settings.

#include "TrackGunAbility.h"
#include "SpeedableInterface.h"
#include "SlowableInterface.h"

void UTrackGunAbility::ApplyEffect(AActor* Target) {

	switch (GunState) {
		case EGunStateHandler::Freeze:
			if (CanFreezeObject()) {
				ApplyFreezeEffect(Target);
			}
		break;

		case EGunStateHandler::Speed:
			if (CanSpeedObject()) {
				ApplySpeedUpEffect(Target);
			}
		break;

		default:
			break;
	}
}

void UTrackGunAbility::ApplyFreezeEffect(AActor* Target) {

	if (Target->GetClass()->ImplementsInterface(USlowableInterface::StaticClass())) {
		
		ISlowableInterface::Execute_ApplySlowEffect(Target);
	}
}

void UTrackGunAbility::ApplySpeedUpEffect(AActor* Target) {

	if (Target->GetClass()->ImplementsInterface(USpeedableInterface::StaticClass())) {

		ISpeedableInterface::Execute_ApplySpeedEffect(Target);
	}
}

void UTrackGunAbility::ChangeGunEffect(){

	//Toggle between Slow and Speed effects
	if (GunState == EGunStateHandler::Freeze) {

		GunState = EGunStateHandler::Speed;

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Speed mode"));
		}
	}
	else {
		GunState = EGunStateHandler::Freeze;

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Slow mode"));
		}
	}

}