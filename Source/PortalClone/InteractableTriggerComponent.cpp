// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableTriggerComponent.h"

#include "PortalCloneCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values for this component's properties
UInteractableTriggerComponent::UInteractableTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
 }

void UInteractableTriggerComponent::OnRegister()
{
	Super::OnRegister();

	AActor* OwnerActor = GetOwner();

	if (!OwnerActor)
		return;

	//Sphere Collider
	TriggerSphere = NewObject<USphereComponent>(OwnerActor, TEXT("SphereColliderTrigger"));
	TriggerSphere->InitSphereRadius(200.f);
	TriggerSphere->SetupAttachment(OwnerActor->GetRootComponent());
	TriggerSphere->RegisterComponent();

	//Widgetcomponent
	WidgetComponent = NewObject<UWidgetComponent>(OwnerActor, TEXT("WidgetColliderTrigger"));
	WidgetComponent->SetupAttachment(GetOwner()->GetRootComponent());
	WidgetComponent->SetRelativeTransform(FTransform(
	FRotator(0, 90, 0),
		FVector(0, 0, 250),
		FVector(1.75f, 0.25f, 0.25f)
	));

	if (TriggerKeyWidgetClass)
	{
		WidgetComponent->SetWidgetClass(TriggerKeyWidgetClass);
	}
	
	WidgetComponent->SetHiddenInGame(true);
	WidgetComponent->RegisterComponent();

	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this,
		&UInteractableTriggerComponent::OverlapBegin);
	TriggerSphere->OnComponentEndOverlap.AddDynamic(this,
		&UInteractableTriggerComponent::OverlapEnd);
}

void UInteractableTriggerComponent::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetOwner())
	{
		if (OtherActor->IsA<APortalCloneCharacter>())
		{
			if (IsValid(WidgetComponent))
			{
				WidgetComponent->SetHiddenInGame(false);
				WidgetComponent->SetVisibility(true);
			}
		}
	}
}

void UInteractableTriggerComponent::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != GetOwner())
	{
		if (OtherActor->IsA<APortalCloneCharacter>())
		{
			if (IsValid(WidgetComponent))
			{
				WidgetComponent->SetHiddenInGame(true);
				WidgetComponent->SetVisibility(false);
			}
		}
	}
}

