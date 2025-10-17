// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VFXBaseComponent.h"
#include "Components/ActorComponent.h"
#include "RecallVFXComponent.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTALCLONE_API URecallVFXComponent : public UVFXBaseComponent
{
	GENERATED_BODY()
	
public: 	
	// Sets default values for this component's properties
	URecallVFXComponent();
	void PlayRecallVFX(const TArray<FVector>& RecallPath, AActor* Actor);
	virtual void StopVFX() override;

protected:
	UPROPERTY(EditAnywhere, Category = "VFX")
	FName RecallVFXName;
};
