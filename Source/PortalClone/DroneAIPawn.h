// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DroneAIPawn.generated.h"

class APatrolPoints;
class USlowLaserComponent;
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

	//return the Patrol Points' map
	TMap<int, TArray<APatrolPoints*>> GetPatrolPoints(){return PatrolPointMap; }
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Drone AI")
	UStaticMeshComponent* DroneAIMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drone AI|Movement")
	UFloatingPawnMovement* DroneMovement;
	
	UPROPERTY(EditAnywhere, Category="Drone AI|Patrol Points")
	TArray<APatrolPoints*> PatrolPoints;

	//Save the patrol point from the PatrolPoint with their floor that belongs to them
	TMap<int, TArray<APatrolPoints*>> PatrolPointMap;
	
public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess))
	TObjectPtr<USlowLaserComponent> SlowLaserComponent;
};
