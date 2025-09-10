// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DroneAIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;

UCLASS()
class PORTALCLONE_API ADroneAIController : public AAIController
{
	GENERATED_BODY()

public :
	ADroneAIController();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drone AI|Perception")
	UAIPerceptionComponent* DronePerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drone AI|Perception")
	UAISenseConfig_Sight* DronePerceptionSight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone AI|BT")
	UBehaviorTree* DroneBehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone AI|BT|KeyName")
	FName TargetKeyName;
	
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
