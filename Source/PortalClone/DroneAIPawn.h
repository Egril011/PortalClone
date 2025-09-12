// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DroneAIPawn.generated.h"

class UBehaviorTree;
class UBoxComponent;
class ULaserComponent;
class UFloatingPawnMovement;

UCLASS()
class PORTALCLONE_API ADroneAIPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADroneAIPawn();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Drone AI")
	UBehaviorTree* DefaultBehaviorTree;

protected:
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Drone AI")
	UStaticMeshComponent* DroneAIMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drone AI|Movement")
	UFloatingPawnMovement* DroneMovement;
	
public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;	
};
