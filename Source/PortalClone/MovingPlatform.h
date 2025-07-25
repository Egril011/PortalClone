// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class PORTALCLONE_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform")
	USceneComponent* StartPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform")
	USceneComponent* EndPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimerSpeed = 0.5f;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 200.0f;

	UPROPERTY(EditAnywhere)
	float WaitTime = 2.0f;

private:
	bool bMovingToTarget = false;

	float CurrentWaitTime = 0.0f;

	bool bIsWaiting = false;

	FVector StartLocation;
	FVector EndLocation;


};
