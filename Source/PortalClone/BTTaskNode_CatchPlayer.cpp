// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_CatchPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTaskNode_CatchPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (IsValid(BBComp))
		return EBTNodeResult::Failed;

	bool bIsCatching = BBComp->GetValueAsBool(bIsTouchingTarget.SelectedKeyName);
	
	if (!bIsCatching)
		return EBTNodeResult::Failed;

	return EBTNodeResult::Succeeded;
}
