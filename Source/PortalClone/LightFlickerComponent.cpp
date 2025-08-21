// Fill out your copyright notice in the Description page of Project Settings.


#include "LightFlickerComponent.h"

#include "Components/LightComponent.h"

// Sets default values for this component's properties
ULightFlickerComponent::ULightFlickerComponent() : TimerHandlerIntervalMin(0), TimerHandlerIntervalMax(0),
                                                   LightIntensityMin(0),
                                                   LightIntensityMax(0)
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void ULightFlickerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	LightFlicker = GetOwner()->FindComponentByClass<ULightComponent>();

	if (!LightFlicker)
	{
		UE_LOG(LogTemp, Error, TEXT("Light Null"));
		return;
	}

	// to make sure IntervalMax > IntervalMin
	if (TimerHandlerIntervalMax < TimerHandlerIntervalMin)
		TimerHandlerIntervalMax = TimerHandlerIntervalMin + 1.0f;

	// to make sure IntensityMax > IntensityMin
	if (LightIntensityMax < LightIntensityMin)
		LightIntensityMax = LightIntensityMin + 1.0f;

	//Start the Timer
	float TimerTime = FMath::FRandRange(TimerHandlerIntervalMin, TimerHandlerIntervalMax);
	
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandleFlicker,
		this,
		&ULightFlickerComponent::Flickering,
		TimerTime,
		false);
}


void ULightFlickerComponent::Flickering()
{
	if (!IsValid(LightFlicker))
		return;
	
	float TargetIntensity = FMath::FRandRange(LightIntensityMin, LightIntensityMax);

	if (FMath::FRand() < 0.03)
		TargetIntensity = 0;

	LightFlicker->SetIntensity(TargetIntensity);
	
	float NewTimerTime = FMath::FRandRange(TimerHandlerIntervalMin, TimerHandlerIntervalMax);

	GetWorld()->GetTimerManager().SetTimer(TimerHandleFlicker,
		this,
		&ULightFlickerComponent::Flickering,
		NewTimerTime,
		false);
}

