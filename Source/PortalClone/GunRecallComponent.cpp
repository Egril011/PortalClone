// Fill out your copyright notice in the Description page of Project Settings.


#include "GunRecallComponent.h"
#include "RecallableInterface.h"

// Sets default values for this component's properties
UGunRecallComponent::UGunRecallComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGunRecallComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UGunRecallComponent::Recall(const FHitResult& HitResult)
{
	AActor* HitActor = HitResult.GetActor();

	if (!IsValid(HitActor))
		return;

	if (HitActor->Implements<URecallableInterface>())
	{
		IRecallableInterface::Execute_Recallable(HitActor);
	}
}



