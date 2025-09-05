// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_StartLaserCharge.generated.h"

/**
 * 
 */
UCLASS()
class PORTALCLONE_API UBTTaskNode_StartLaserCharge : public UBTTaskNode
{
	GENERATED_BODY()
	UBTTaskNode_StartLaserCharge();

	UPROPERTY(EditAnywhere, Category = "BB|Variable")
	FBlackboardKeySelector CurrentLaserCompKey;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
