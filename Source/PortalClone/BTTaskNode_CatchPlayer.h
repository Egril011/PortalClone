// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_CatchPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PORTALCLONE_API UBTTaskNode_CatchPlayer : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, Category = "CatchPlayer|variable", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector bIsTouchingTarget;
};
