// Fill out your copyright notice in the Description page of Project Settings.


#include "GunFreezeComponent.h"

#include "FreezableInterface.h"
#include "FreezeComponent.h"
#include "Components/WidgetComponent.h"


// Sets default values for this component's properties
UGunFreezeComponent::UGunFreezeComponent()
{
}

void UGunFreezeComponent::FreezeObject(FHitResult HitResult)
{
	AActor* HitActor = HitResult.GetActor();
	if (!IsValid(HitActor))
		return;
	
	if(!HitActor->Implements<UFreezableInterface>())
		return;

	IFreezableInterface::Execute_ApplyFreezeEffect(HitActor);
}


