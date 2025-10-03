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
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	TObjectPtr<APawn> CurrentPawn = nullptr;
	TObjectPtr<UBlackboardComponent> BBComp = nullptr;

	UPROPERTY(EditAnywhere, Category="Patrol", meta=(AllowPrivateAccess))
	float Speed = 5.f;

	UPROPERTY(EditAnywhere, Category="Patrol", meta=(AllowPrivateAccess))
	float AcceptanceRadius = 150.f;

	UPROPERTY(EditAnywhere, Category = "Patrol", meta=(AllowPrivateAccess))
	float Radius = 500.f;

	FVector TargetLocation = FVector(0.f, 0.f,0.f);
	
	//Get a reachable point thanks to the NavMesh
	bool ReturnReachablePoint(FVector PawnLocation, FVector& OutNewPawnLocation);
};
