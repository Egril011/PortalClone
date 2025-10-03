// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GoInvestigate.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_GoInvestigate::UBTTask_GoInvestigate()
{
	NodeName = "Go Investigate";
}

EBTNodeResult::Type UBTTask_GoInvestigate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BBComp = OwnerComp.GetBlackboardComponent();
	if (!BBComp)
		return EBTNodeResult::Failed;

	AIController = OwnerComp.GetAIOwner();
	if (!AIController)
		return EBTNodeResult::Failed;

	CurrentPawn = AIController->GetPawn();
	if (!CurrentPawn)
		return EBTNodeResult::Failed;
	
	//Get the last target location
	LastTargetLocation = BBComp->GetValueAsVector(LastTargetLocationKey.SelectedKeyName);
	LastTargetLocation.Z = CurrentPawn->GetActorLocation().Z;

	bNotifyTick = true;
	return EBTNodeResult::InProgress;
}

void UBTTask_GoInvestigate::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (!CurrentPawn)
		return;

	//Move the AI to the last place he's seen the target
	FVector ToTarget = LastTargetLocation - CurrentPawn->GetActorLocation();
	CurrentPawn->AddMovementInput(ToTarget.GetSafeNormal());

	//Get the Distance between the pawn and the target
	if (ToTarget.Size2D() < AcceptanceRadius)
	{
		BBComp->ClearValue(LastTargetLocationKey.SelectedKeyName);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
