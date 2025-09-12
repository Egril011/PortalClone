// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Patrol.h"

#include "AIController.h"
#include "NavigationSystem.h"

UBTTaskNode_Patrol::UBTTaskNode_Patrol()
{
	NodeName = TEXT("Patrol");
}

EBTNodeResult::Type UBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get the Pawn and its location
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
		return EBTNodeResult::Failed;

	APawn* CurrentPawn = AIController->GetPawn();
	if (!CurrentPawn)
		return EBTNodeResult::Failed;

	FVector PawnLocation = CurrentPawn->GetActorLocation();

	//Get the NavMesh to get a random point
	UNavigationSystemV1* NavigationSystem =  FNavigationSystem::GetCurrent<UNavigationSystemV1>(CurrentPawn->GetWorld());
	if (!NavigationSystem)
		return EBTNodeResult::Failed;

	FNavLocation NavLocation;
	if (!NavigationSystem->GetRandomPointInNavigableRadius(PawnLocation, Radius, NavLocation))
		return EBTNodeResult::Failed;

	return EBTNodeResult::InProgress;
}
