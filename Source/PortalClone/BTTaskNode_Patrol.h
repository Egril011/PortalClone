// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_Patrol.generated.h"

class APatrolPoints;
class ADroneAIPawn;
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
	TObjectPtr<ADroneAIPawn> DroneAI = nullptr;
	TObjectPtr<AActor> OwnerActor = nullptr;
	TArray<APatrolPoints*> PatrolPointFloor;
	
	float NearestPoint = 0.f;
	int IndexPatrolPoint = 0;
	int StartingPoint = 0;

	UPROPERTY(EditAnywhere, Category = "Patrol|Variable", meta = (AllowPrivateAccess = "true"))
	float AcceptanceRadius = 150.f;

	UPROPERTY(EditAnywhere, Category = "BB|Variable")
	FBlackboardKeySelector CurrentFloor;

	UPROPERTY(EditAnywhere, Category = "BB|Variable")
	FBlackboardKeySelector bChangeFloor;

	void GetNearestPatrolPoint(const TArray<APatrolPoints*>& PatrolPoints);
	void MoveToNextPatrolPoint(const TArray<APatrolPoints*>& PatrolPoints, float DeltaTime, UBehaviorTreeComponent& OwnerComp);
};
