// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_UseLaser.generated.h"

/**
 * 
 */
UCLASS()
class PORTALCLONE_API UBTTaskNode_UseLaser : public UBTTaskNode
{
	GENERATED_BODY()
	UBTTaskNode_UseLaser();

	UPROPERTY(EditAnywhere, Category = "BB|Variable")
	FBlackboardKeySelector CurrentLaserCompKey;

	UPROPERTY(EditAnywhere, Category = "BB|Variable")
	FBlackboardKeySelector TargetLaserCompKey;

	UBehaviorTreeComponent* BehaviorTree = nullptr;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UFUNCTION()
	void LaserFinished();
};
