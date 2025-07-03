// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PlayerRespawn.generated.h"

UCLASS()
class PORTALCLONE_API APlayerRespawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerRespawn();

protected:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY()
	UBoxComponent* BoxCollider;

	UFUNCTION()
	void BeginPlay();

private:
	FVector SpawnLocation_;
	FRotator SpawnRotation_;

	UPROPERTY(EditAnywhere)
	USceneComponent* SceneSpawn;
};

