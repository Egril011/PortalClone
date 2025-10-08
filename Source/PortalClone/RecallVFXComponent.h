// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RecallVFXComponent.generated.h"


class UNiagaraSystem;
class UNiagaraComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTALCLONE_API URecallVFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URecallVFXComponent();

	//Play the recall vfx
	void PlayRecallVFX(const TArray<FVector>& RecallPath, AActor* Actor);

	//Stop the recall vfx
	void StopRecallVFX();

private:
	TObjectPtr<UNiagaraComponent> ActiveVFX;

	UPROPERTY(EditAnywhere, Category="RecallVFX", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraSystem> RecallVFXSystem;
};
