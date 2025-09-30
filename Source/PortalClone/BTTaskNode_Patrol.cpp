// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Patrol.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "Math/UnitConversion.h"

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

	//Get the NavMesh
	CurrentNav =  FNavigationSystem::GetCurrent<UNavigationSystemV1>(CurrentPawn->GetWorld());
	if (!CurrentNav)
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
	
	//Get the Pawn Location
	FVector PawnLocation = CurrentPawn->GetActorLocation();

	//Get the Distance between the two points
	FVector NewTargetLocation = FVector(TargetLocation.X,TargetLocation.Y, PawnLocation.Z);
	FVector ToTarget = NewTargetLocation - PawnLocation;
	float Distance = FVector(ToTarget.X, ToTarget.Y, 0.f).Size();

	if (Distance < AcceptanceRadius)
	{
		UE_LOG(LogTemp,Warning,TEXT("Distance < AcceptanceRadius"));
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	//Move the pawn toward the target
	FVector MoveDirection = FVector(ToTarget.X, ToTarget.Y, 0).GetSafeNormal();
	FVector Direction = MoveDirection * Speed * DeltaSeconds;
	
	CurrentPawn->SetActorLocation(CurrentPawn->GetActorLocation() + Direction,true);
	CurrentPawn->SetActorRotation(MoveDirection.Rotation());
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
		return true;
	}
	 return false;
}
