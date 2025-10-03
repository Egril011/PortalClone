// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_GoInvestigate.generated.h"

/**
 * 
 */
UCLASS()
class PORTALCLONE_API UBTTask_GoInvestigate : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_GoInvestigate();

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
private:
	UPROPERTY(EditAnywhere, Category = "BB|Variable", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector LastTargetLocationKey;

	UPROPERTY(EditAnywhere, Category = "Go Investigate", meta = (AllowPrivateAccess = "true"))
	float AcceptanceRadius = 150.f;

	UPROPERTY(EditAnywhere, Category = "Go Investigate", meta = (AllowPrivateAccess = "true"))
	float Speed = 150.f;
	
	TObjectPtr<APawn> CurrentPawn = nullptr;
	TObjectPtr<UBlackboardComponent> BBComp = nullptr;
	TObjectPtr<AAIController> AIController = nullptr;
	FVector LastTargetLocation;
	FTimerHandle GoInverstigateTimerHandle;
};
