// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Patrol.h"

#include "AIController.h"
#include "DroneAIPawn.h"
#include "PatrolPoints.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskNode_Patrol::UBTTaskNode_Patrol()
{
	NodeName = TEXT("PatrolAIFly");
}

EBTNodeResult::Type UBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!IsValid(AIController)) 
		return EBTNodeResult::Failed;

	if (!AIController->GetPawn()->IsA<ADroneAIPawn>())
		return EBTNodeResult::Failed;

	DroneAI = Cast<ADroneAIPawn>(AIController->GetPawn());
	if (!IsValid(DroneAI))
		return EBTNodeResult::Failed;

	//Get which floor the AI is
	IndexPatrolPoint = 0;
	int Floor = AIController->GetBlackboardComponent()->GetValueAsInt(CurrentFloor.SelectedKeyName);
	
	//Get the PatrolPoints that match with the floor
	if (DroneAI->GetPatrolPoints().Contains(Floor))
	{
		PatrolPointFloor = DroneAI->GetPatrolPoints()[Floor];
	}
	
	GetNearestPatrolPoint(PatrolPointFloor);
	StartingPoint = IndexPatrolPoint;
	
	bNotifyTick = true;
	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	MoveToNextPatrolPoint(PatrolPointFloor, DeltaSeconds, OwnerComp);
}

void UBTTaskNode_Patrol::GetNearestPatrolPoint(const TArray<APatrolPoints*>& PatrolPoints)
{
	if (!IsValid(DroneAI))
		return;

	if (PatrolPoints.Num() == 0)
		return;
	
	//Get the first point location  
	NearestPoint = FVector::DistSquared(PatrolPoints[0]->GetActorLocation(), DroneAI->GetActorLocation());

	//Search the nearest point from the AI
	for (int i = 0; i < PatrolPoints.Num(); i++)
	{
		APatrolPoints* p = PatrolPoints[i];
		float Distance = FVector::DistSquared(p->GetActorLocation(), DroneAI->GetActorLocation());
		if (Distance < NearestPoint)
		{
			NearestPoint = Distance;
			IndexPatrolPoint = i; 
		}
	}
}

void UBTTaskNode_Patrol::MoveToNextPatrolPoint(const TArray<APatrolPoints*>& PatrolPoints, float DeltaTime, UBehaviorTreeComponent& OwnerComp)
{
	if (IndexPatrolPoint < 0 || IndexPatrolPoint >= PatrolPoints.Num())
		return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	
	//Move the AI to the next patrol point from the Array
	FVector ToPoint = PatrolPoints[IndexPatrolPoint]->GetActorLocation() - DroneAI->GetActorLocation();
	FVector Direction = ToPoint.GetSafeNormal();
	DroneAI->AddMovementInput(Direction, 1.f);

	//Make the AI rotate
	FRotator Rotation = ToPoint.Rotation();
	Rotation.Pitch = 0.f;
	DroneAI->SetActorRotation(FMath::RInterpTo(DroneAI->GetActorRotation(), Rotation, DeltaTime, 5.f));

	if (ToPoint.Size() < AcceptanceRadius)
	{
		//make the AI goes to each point (circular buffer)
		IndexPatrolPoint = (IndexPatrolPoint + 1) % PatrolPoints.Num(); 
		
		if (IndexPatrolPoint == StartingPoint)
		{
			//Change the fl oor when the AI have gone to each points
			OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsBool(bChangeFloor.SelectedKeyName, true);
			return FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}
