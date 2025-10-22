// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_GoNextFloor.generated.h"

/**
 * 
 */
UCLASS()
class PORTALCLONE_API UBTTaskNode_GoNextFloor : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskNode_GoNextFloor();

protected:
	EBTNodeResult::Type ExecuteTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, Category = "BB|Variable")
	FBlackboardKeySelector CurrentFloor;

	UPROPERTY(EditAnywhere, Category = "BB|Variable")
	FBlackboardKeySelector bChangeFloor;
};
