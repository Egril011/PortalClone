// Fill out your copyright notice in the Description page of Project Settings.


#include "GunRecallComponent.h"
#include "RecallableInterface.h"
#include "RecallComponent.h"

// Sets default values for this component's properties
UGunRecallComponent::UGunRecallComponent() : ActorRef(nullptr),
												RecallComponent(nullptr),
												bIsRecalling(false)
{
	PrimaryComponentTick.bCanEverTick = false;
}

/*This method is used to execute the Recallable via the interface and to prevent the player
 * from recalling two objects at the same time*/
void UGunRecallComponent::Recall(const FHitResult& HitResult)
{
	if (bIsRecalling)
		return;

	ActorRef = HitResult.GetActor();
	
	if (!IsValid(ActorRef))
		return;
	
	if (!ActorRef->Implements<URecallableInterface>())
		return;

	RecallComponent = ActorRef->FindComponentByClass<URecallComponent>();

	if (!IsValid(RecallComponent))
		return;

	RecallComponent->OnRecallFinished.RemoveDynamic(this, &UGunRecallComponent::CleanUp);
	RecallComponent->OnRecallFinished.AddDynamic(this, &UGunRecallComponent::CleanUp);

	IRecallableInterface::Execute_Recallable(ActorRef);
	
	bIsRecalling = true;
}
/**/
void UGunRecallComponent::CancelRecall()
{
	if (!IsValid(ActorRef))
		return;

	if (ActorRef->Implements<URecallableInterface>())
	{
		IRecallableInterface::Execute_CancelRecall(ActorRef);
		CleanUp();
	}
}

void UGunRecallComponent::CleanUp()
{
	if (IsValid(RecallComponent))
	{
		RecallComponent->OnRecallFinished.RemoveDynamic(this, &UGunRecallComponent::CleanUp);
		RecallComponent = nullptr;
	}
	
	ActorRef = nullptr;
	bIsRecalling = false;
}