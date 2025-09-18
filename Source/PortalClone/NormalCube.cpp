// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalCube.h"

#include "FreezeComponent.h"
#include "RecallComponent.h"
#include "RoundProgressBarWidget.h"
#include "Components/WidgetComponent.h"

// Sets default values
ANormalCube::ANormalCube()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	//Create the component
	RecallComponent = CreateDefaultSubobject<URecallComponent>(TEXT("RecallComponent"));
	FreezeComponent = CreateDefaultSubobject<UFreezeComponent>(TEXT("FreezeComponent"));

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(StaticMesh);
	WidgetComponent->SetWidgetClass(URoundProgressBarWidget::StaticClass());
}

void ANormalCube::BeginPlay() {

	Super::BeginPlay();
	StaticMesh->SetSimulatePhysics(true);

	if (WidgetComponent)
	{
		if (URoundProgressBarWidget* RoundProgressBarWidget = Cast<URoundProgressBarWidget>(WidgetComponent->GetUserWidgetObject()))
		{
			RoundProgressBarWidget->InitializeOwner(FreezeComponent);
		}
	}
}

void ANormalCube::OnPlatePressed_Implementation() {

}

void ANormalCube::Recallable_Implementation()
{
	if (!RecallComponent)
		return;
	
	RecallComponent->StartRecall();
}

void ANormalCube::CancelRecall_Implementation()
{
	if (!RecallComponent)
		return;
	
	RecallComponent->StopRecall();
}

void ANormalCube::ApplyFreezeEffect_Implementation()
{
	if (!FreezeComponent)
		return;

	FreezeComponent->StartFreezeEffect();
}
