// Fill out your copyright notice in the Description page of Project Settings.


#include "FreezeComponent.h"
#include "Components/WidgetComponent.h"


// Sets default values for this component's properties
UFreezeComponent::UFreezeComponent()
{
}

void UFreezeComponent::StartFreezeEffect()
{
	CreateFreezeWidget();
}

/*Create the Freeze Widget above the actor*/
void UFreezeComponent::CreateFreezeWidget()
{
	AActor* Owner = GetOwner();
	if (!IsValid(Owner))
		return;

	if (!IsValid(FreezeWidgetClass))
		return;

	//Creation
	UWidgetComponent* WidgetComp = NewObject<UWidgetComponent>(Owner);
	if (!IsValid(WidgetComp))
		return;

	WidgetComp->SetWidgetClass(FreezeWidgetClass);
	WidgetComp->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	WidgetComp->SetTwoSided(true);

	//Set its location and its size
	WidgetComp->SetWidgetSpace(EWidgetSpace::World);
	
	WidgetComp->SetRelativeLocation(FVector(0.f, 0.f, 220.f));
	WidgetComp->SetRelativeScale3D(FVector(0.75f, 0.75f, 0.75f));
	
	WidgetComp->RegisterComponentWithWorld(GetWorld());
}
