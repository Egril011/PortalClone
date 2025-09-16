// Fill out your copyright notice in the Description page of Project Settings.


#include "RoundProgressBarWidget.h"

#include "Components/Image.h"

void URoundProgressBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (!ProgressBar || !BaseMaterial)
		return;

	DynamicMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);

	if (!DynamicMaterial)
		return;

	ProgressBar->SetBrushFromMaterial(DynamicMaterial);
	SetPercentage(1);
}

/*Set the round progress bar's percentage*/
void URoundProgressBarWidget::SetPercentage(float percentage) const
{
	if (!DynamicMaterial)
		return;

	DynamicMaterial->SetScalarParameterValue(PercentageKeyName,
		FMath::Clamp(percentage, 0.f, 1.f));
}
