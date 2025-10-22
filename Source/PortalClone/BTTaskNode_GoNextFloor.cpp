// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_GoNextFloor.h"

#include "AIController.h"
#include "DroneAIPawn.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskNode_GoNextFloor::UBTTaskNode_GoNextFloor()
{
	NodeName = "Go Next Floor";
}

EBTNodeResult::Type UBTTaskNode_GoNextFloor::ExecuteTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	int currentFloor = OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsInt(CurrentFloor.SelectedKeyName);
	if (!OwnerComp.GetAIOwner()->GetPawn()->IsA<ADroneAIPawn>())
		return EBTNodeResult::Failed;
	
	ADroneAIPawn* DroneAI = Cast<ADroneAIPawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (!IsValid(DroneAI))
		return EBTNodeResult::Failed;

	//See if the next floor exists
	if (DroneAI->GetPatrolPoints().Contains(currentFloor + 1))
	{
		currentFloor++;
		OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsInt(CurrentFloor.SelectedKeyName, currentFloor);
	}
	else
	{
		//if next currentfloor doesn't exist go to the previous floor
		currentFloor--;
		OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsInt(CurrentFloor.SelectedKeyName, currentFloor);
	}

	OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsBool(bChangeFloor.SelectedKeyName, false);
	return EBTNodeResult::Succeeded;
}
