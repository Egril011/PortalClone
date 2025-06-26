// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubeRespawn.generated.h"

UCLASS()
class PORTALCLONE_API ACubeRespawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACubeRespawn();
	
	//Respawn the cube that was detroyed
	void Respawn(UClass* Actor);

	void BeginPlay();

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	USceneComponent* SpawnCubeLocalisation;

private:
	FVector Location;
	FRotator Rotator;
};
