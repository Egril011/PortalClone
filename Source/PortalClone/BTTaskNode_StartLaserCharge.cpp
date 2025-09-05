// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_StartLaserCharge.h"

#include "AIController.h"
#include "LaserComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskNode_StartLaserCharge::UBTTaskNode_StartLaserCharge()
{
	NodeName = "StartLaserCharge";
}

EBTNodeResult::Type UBTTaskNode_StartLaserCharge::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (!IsValid(BBComp))
	{
		UE_LOG(LogTemp,Warning,TEXT("IsValid(BBComp)"));
		return EBTNodeResult::Failed;
	}

	APawn* SelfPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!IsValid(SelfPawn))
	{
		UE_LOG(LogTemp,Warning,TEXT("IsValid(SelfPawn)"));
		return EBTNodeResult::Failed;
	}
	
	UObject* ObjectComponent = BBComp->GetValueAsObject(CurrentLaserCompKey.SelectedKeyName);
	if (!IsValid(ObjectComponent))
	{
		UE_LOG(LogTemp,Warning,TEXT("IsValid(Object)"));
		return EBTNodeResult::Failed;
	}
	
	ULaserComponent* LaserComp = Cast<ULaserComponent>(ObjectComponent);
	if (!IsValid(LaserComp))
	{
		UE_LOG(LogTemp,Warning,TEXT("IsValid(LaserComp)"));
		return EBTNodeResult::Failed;
	}
		

	UE_LOG(LogTemp,Warning,TEXT("LaserComp:%s"),*LaserComp->GetName());
	LaserComp->FireLaser();
	
	return EBTNodeResult::Succeeded;
}
