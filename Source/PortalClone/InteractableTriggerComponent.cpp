// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableTriggerComponent.h"

#include "PortalCloneCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values for this component's properties
UInteractableTriggerComponent::UInteractableTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	//Sphere Collider
	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerSphere"));
	TriggerSphere->InitSphereRadius(200.f);
	TriggerSphere->SetupAttachment(this);
	
	//Widget component
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(this);
	WidgetComponent->SetWidgetSpace(EWidgetSpace::World);
	WidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	WidgetComponent->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	WidgetComponent->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	WidgetComponent->SetPivot(FVector2D(0.5f, 0.5f));       
	WidgetComponent->SetTwoSided(true);                     
	WidgetComponent->SetHiddenInGame(true);
 }

void UInteractableTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (TriggerSphere)
	{
		TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &UInteractableTriggerComponent::OverlapBegin);
		
		TriggerSphere->OnComponentEndOverlap.AddDynamic(this, &UInteractableTriggerComponent::OverlapEnd);
	}
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

