// Fill out your copyright notice in the Description page of Project Settings.


#include "RecallVFXComponent.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraDataInterfaceArrayFunctionLibrary.h"

// Sets default values for this component's properties
URecallVFXComponent::URecallVFXComponent()
{
}

void URecallVFXComponent::PlayRecallVFX(const TArray<FVector>& RecallPath, AActor* Actor)
{
	if (RecallPath.IsEmpty() || !IsValid(Actor))
		return;
	
	if (ActiveVFX)
		StopRecallVFX();

	//Create the VFX at the Object location
	ActiveVFX = UNiagaraFunctionLibrary::SpawnSystemAttached(
		RecallVFXSystem,
		Actor->GetRootComponent(),
		NAME_None,
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		EAttachLocation::KeepRelativeOffset,
		true);

	if (!IsValid(ActiveVFX))
		return;

	//Set the Niagara's array
	UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayPosition(
		ActiveVFX,
		FName("PathPosition"),
		RecallPath
	);

	//Set the Niagara's int
	ActiveVFX->SetIntParameter(TEXT("PathCount"), RecallPath.Num());
}

void URecallVFXComponent::StopRecallVFX()
{
	if (ActiveVFX) {
		ActiveVFX->Deactivate();
		ActiveVFX->DestroyComponent();
		ActiveVFX = nullptr;
	}
}

