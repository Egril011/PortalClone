// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_FlyChasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class PORTALCLONE_API UBTTaskNode_FlyChasePlayer : public UBTTaskNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "BB|Variable")
	FBlackboardKeySelector TargetActor;

	UPROPERTY(EditAnywhere, Category = "Chasing")
	int Speed = 150.f;

	UPROPERTY(EditAnywhere, Category = "Chasing")
	float AcceptanceRadius = 150.f;

	UPROPERTY(EditAnywhere, Category = "Chasing")
	float ElevationHeight = 220.f;
	
	UBTTaskNode_FlyChasePlayer();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
