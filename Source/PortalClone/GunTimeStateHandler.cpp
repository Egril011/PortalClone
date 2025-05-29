// Fill out your copyright notice in the Description page of Project Settings.

#include "GunTimeStateHandler.h"

GunTimeStateHandler::GunTimeStateHandler()
{
}

GunTimeStateHandler::~GunTimeStateHandler()
{
}

//Apply the effect based on the gun' state
void GunTimeStateHandler::ApplyState(AActor* Target, UMyGameInstance* GI) {
	
	if (!Target && !GI)
		return;

	switch (GI->CurrentGunState)
	{
		case EGunTimeState::Slow:
			SlowEffect(Target);
			break;

		case EGunTimeState::Speed:
			SpeedUpEffect(Target);
			break;

		default:
			break;
	}
}

//Apply the slow effect to the Target by calling its interface 
void GunTimeStateHandler::SlowEffect(AActor* Target) {

	if (!Target) 
		return;	

	//looking if the Target has the Slowable interface
	if (Target->Implements<USlowableInterface>()) {
		
		ISlowableInterface* Slowable = Cast<ISlowableInterface>(Target);
		if (Slowable) {

			Slowable->ApplySlowEffect();
		}
	}
}

//Apply the speed effect to the Target by calling its interface
void GunTimeStateHandler::SpeedUpEffect(AActor* Target)
{
	if (!Target)
		return;

	//looking if the Target has the Speedable interface
	if (Target->Implements<USpeedableInterface>()) {

		ISpeedableInterface* Speedable = Cast<ISpeedableInterface>(Target);
		if (Speedable) {
			Speedable->Applyspeed();
		}
	}
}