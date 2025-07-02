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
	
	//Spawn the Actor 
	AActor* SpawnActor();

	void BeginPlay();

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	USceneComponent* SpawnCubeLocalisation;

	UPROPERTY(EditInstanceOnly)
	TSubclassOf<AActor> Target;

	UPROPERTY(EditInstanceOnly)
	int ListSize;

	UPROPERTY()
	TArray<AActor*> ActorList;

private:
	FVector Location;
	FRotator Rotator;

	void InitializePool();
};
