// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorPressedPlate_Freeze.h"
#include "FreezeComponent.h"
#include "RoundProgressBarWidget.h"
#include "Components/WidgetComponent.h"

ADoorPressedPlate_Freeze::ADoorPressedPlate_Freeze()
{
	FreezeComponent= CreateDefaultSubobject<UFreezeComponent>(TEXT("FreezeComponent"));
	WidgetComponent= CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(RootComponent);
}

void ADoorPressedPlate_Freeze::BeginPlay()
{
	Super::BeginPlay();

	  if (IsValid(WidgetComponent) && IsValid(FreezeComponent))
	  {
	  	WidgetComponent->SetVisibility(false);
	  	
	  	 if (URoundProgressBarWidget* RoundProgressBar = Cast<URoundProgressBarWidget>(WidgetComponent->GetUserWidgetObject()))
	  	 {
		  	 RoundProgressBar->InitializeOwner(FreezeComponent);
	  	 }
	  }
}

void ADoorPressedPlate_Freeze::ApplyFreezeEffect_Implementation()
{
	if (IsValid(FreezeComponent) && IsValid(WidgetComponent))
	{
		if (FreezeComponent->IsFrozen())
		{
			WidgetComponent->SetVisibility(false);
			FreezeComponent->CancelFreezeEffect();
			FreezeComponent->OnEndFreeze.RemoveDynamic(this, &ADoorPressedPlate_Freeze::PlayCloseDoor);
			return;
		}

		WidgetComponent->SetVisibility(true);
		FreezeComponent->StartFreezeEffect();
		FreezeComponent->OnEndFreeze.AddUniqueDynamic(this, &ADoorPressedPlate_Freeze::PlayCloseDoor);
	}
}

void ADoorPressedPlate_Freeze::PlayCloseDoor()
{
	if (IsValid(FreezeComponent) && FreezeComponent->IsFrozen())
		return;
	 
	Super::PlayCloseDoor();
}
