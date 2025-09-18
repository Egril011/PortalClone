// Fill out your copyright notice in the Description page of Project Settings.


#include "RoundProgressBarWidget.h"

#include "FreezeComponent.h"
#include "Components/Image.h"
#include "Components/WidgetComponent.h"

void URoundProgressBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (!ProgressBarImage || !BaseMaterial)
		return;

	DynamicMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);
	if (!DynamicMaterial)
		return;
  
	ProgressBarImage->SetBrushFromMaterial(DynamicMaterial);
	SetPercentage(1);
}

//Get the Object that hold the ProgressBar Interface
void URoundProgressBarWidget::InitializeOwner(UObject* Owner)
{
	if (!IsValid(Owner))
		return;

	if (Owner->Implements<UProgressBarInterface>())
	{
		ProgressBarScript.SetObject(Owner);
		ProgressBarScript.SetInterface(Cast<IProgressBarInterface>(Owner));

		ProgressBarScript->GetProgressBarDelegation()->AddUniqueDynamic(this, &URoundProgressBarWidget::SetPercentage);
		SetPercentage(1);
	}
}

/*Set the percentage*/
void URoundProgressBarWidget::SetPercentage(float percentage)
{
	if (!DynamicMaterial)
		return;
	
	DynamicMaterial->SetScalarParameterValue(PercentageKeyName,
		FMath::Clamp(percentage, 0.f, 1.f));
}
