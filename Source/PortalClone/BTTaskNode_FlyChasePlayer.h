// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Navigation/PathFollowingComponent.h"
#include "BTTaskNode_FlyChasePlayer.generated.h"
class UFloatingPawnMovement;
/**
 * 
 */
UCLASS()
class PORTALCLONE_API UBTTaskNode_FlyChasePlayer : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UBTTaskNode_FlyChasePlayer();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	

private:
	UPROPERTY(EditAnywhere, Category = "BB|Variable", meta=(AllowPrivateAccess))
	FBlackboardKeySelector TargetActor;

	UPROPERTY(EditAnywhere, Category = "BB|Variable", meta = (AllowPrivateAccess))
	FBlackboardKeySelector bIsTouchingTarget;

	UPROPERTY(EditAnywhere, Category = "BB|Variable", meta=(AllowPrivateAccess))
	FBlackboardKeySelector LastTargetLocationKeyName;
	
	UPROPERTY(EditAnywhere, Category = "Chasing", meta=(AllowPrivateAccess))
	int Speed = 150.f;

	UPROPERTY(EditAnywhere, Category = "Chasing", meta=(AllowPrivateAccess))
	int HeightAI = 150.f;

	UPROPERTY(EditAnywhere, Category = "Chasing", meta=(AllowPrivateAccess))
	float AcceptanceRadius = 150.f;

	UPROPERTY(EditAnywhere, Category = "Chasing", meta=(AllowPrivateAccess))
	float ElevationHeight = 220.f;

	TObjectPtr<APawn> SelfPawn = nullptr;
	TObjectPtr<AActor> Target = nullptr;
	TObjectPtr<UBlackboardComponent> BBComp = nullptr;
	TObjectPtr<AAIController> AIController = nullptr;
	float PawnZLocation = 0.f;
	
};
