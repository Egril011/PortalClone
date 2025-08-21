// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/LightComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "LightFlicker.generated.h"

class ULightFlickerComponent;

UCLASS()
class PORTALCLONE_API ALightFlicker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightFlicker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Flicker")
	ULightComponent* Light;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeleton")
	USkeletalMeshComponent* SkeletalMeshComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Flicker")
	ULightFlickerComponent* LightFlickerComponent;
};
