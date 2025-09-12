// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_Patrol.generated.h"

class UNavigationSystemV1;
/**
 * 
 */
UCLASS()
class PORTALCLONE_API UBTTaskNode_Patrol : public UBTTaskNode
{
	GENERATED_BODY()
public:
	
	UBTTaskNode_Patrol();

protected:
	UPROPERTY(EditAnywhere, Category = "NaveMesh|RadiusThres")
	float Radius = 10.f;

	UPROPERTY(EditAnywhere, Category = "Key")
	FName PawnLocationKey;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
