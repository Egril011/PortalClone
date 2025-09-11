// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_UseLaser.h"

#include "AIController.h"
#include "LaserComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskNode_UseLaser::UBTTaskNode_UseLaser()
{
	NodeName = "UseLaser";
}

EBTNodeResult::Type UBTTaskNode_UseLaser::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	BehaviorTree = &OwnerComp;
	
	if (!IsValid(BBComp))
	{
		return EBTNodeResult::Failed;
	}

	APawn* SelfPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!IsValid(SelfPawn))
	{
		return EBTNodeResult::Failed;
	}

	//Get the Target that is saved in the blackboard value
	UObject* TargetSaved = BBComp->GetValueAsObject(TargetLaserCompKey.SelectedKeyName);
	if (!IsValid(TargetSaved))
		return EBTNodeResult::Failed;

	AActor* TargetActor = Cast<AActor>(TargetSaved);
	if (!IsValid(TargetActor))
		return EBTNodeResult::Failed;
	
	//Get the Laser component and Cast to it 
	UObject* ObjectComponent = BBComp->GetValueAsObject(CurrentLaserCompKey.SelectedKeyName);
	if (!IsValid(ObjectComponent))
	{
		return EBTNodeResult::Failed;
	}
	
	CurrentLaserComp = Cast<ULaserComponent>(ObjectComponent);
	if (!IsValid(CurrentLaserComp))
	{
		return EBTNodeResult::Failed;
	}
	
	CurrentLaserComp->OnFireFinished.AddUniqueDynamic(this, &UBTTaskNode_UseLaser::LaserFinished);
	CurrentLaserComp->StartLaser(TargetActor);
	
	return EBTNodeResult::InProgress;
}

void UBTTaskNode_UseLaser::LaserFinished() 
{
	if (!BehaviorTree)
	{
		FinishLatentTask(*BehaviorTree, EBTNodeResult::Failed);
	}
	else
	{
		FinishLatentTask(*BehaviorTree, CurrentLaserComp->IsLaserSuccess()?
			EBTNodeResult::Succeeded : EBTNodeResult::Failed);
	}
}
