// Fill out your copyright notice in the Description page of Project Settings.

#include "GunTimeStateHandler.h"

GunTimeStateHandler::GunTimeStateHandler()
{
}

GunTimeStateHandler::~GunTimeStateHandler()
{
}

void GunTimeStateHandler::ApplyState(AActor* Target, UMyGameInstance* GI) {

	if (!Target && !GI)
		return;


	switch (GI->CurrentGunState)
	{
		case EGunTimeState::Slow:
			ApplySlow(Target);
			break;

		case EGunTimeState::Speed:
			ApplySpeedUp(Target);
			break;

		case EGunTimeState::Freeze:
			ApplyFreeze(Target);
			break;

		default:
			break;
	}
}

void GunTimeStateHandler::ApplySlow(AActor* Target) {

}

void GunTimeStateHandler::ApplySpeedUp(AActor* Target) {

}

void GunTimeStateHandler::ApplyFreeze(AActor* Target) {

}