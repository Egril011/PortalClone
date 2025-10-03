// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Patrol.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Chaos/PBDSuspensionConstraintData.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Navigation/PathFollowingComponent.h"

UBTTaskNode_Patrol::UBTTaskNode_Patrol()
{
	NodeName = TEXT("Patrol");
}

EBTNodeResult::Type UBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
		return EBTNodeResult::Failed;

	CurrentPawn = AIController->GetPawn();
	if (!CurrentPawn)
		return EBTNodeResult::Failed;
	
	//Get the new reachable point
	if (!ReturnReachablePoint(CurrentPawn->GetActorLocation(), TargetLocation))
		return EBTNodeResult::Failed;
	
	bNotifyTick = true;
	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	if (!CurrentPawn)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	//Move the AI to the Target
	FVector PawnLocation = CurrentPawn->GetActorLocation();
	FVector ToTarget = TargetLocation - PawnLocation;
	FVector Direction = ToTarget.GetSafeNormal2D();
	CurrentPawn->AddMovementInput(Direction, 1.f);
	
	//Get the Distance between the pawn and the target
	if (ToTarget.Size2D() < AcceptanceRadius)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

bool UBTTaskNode_Patrol::ReturnReachablePoint(FVector PawnLocation, FVector& OutNewPawnLocation)
{
	UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(CurrentPawn->GetWorld());
	if (!NavigationSystem)
		return false;
	
		FNavLocation NavLocation;
		if (NavigationSystem->GetRandomReachablePointInRadius(PawnLocation, Radius, NavLocation))
		{
			OutNewPawnLocation = NavLocation.Location;
			OutNewPawnLocation.Z = PawnLocation.Z;
			return true;
		}
	return false;
}
