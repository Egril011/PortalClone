// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_CatchPlayer.h"

#include "MyGameMode.h"
#include "PortalCloneCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBTTaskNode_CatchPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (!IsValid(BBComp))
		return EBTNodeResult::Failed;

	bool bIsCatching = BBComp->GetValueAsBool(bIsTouchingTarget.SelectedKeyName);
	
	if (!bIsCatching)
		return EBTNodeResult::Failed;
	
	//Get the player and its controller
	if (APortalCloneCharacter* Player = Cast<APortalCloneCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		AController* PlayerController = Player->GetController();
		if (!IsValid(PlayerController))
			return EBTNodeResult::Failed;

		AMyGameMode* GM = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (!IsValid(GM))
			return EBTNodeResult::Failed;

		//Respawn the player
		GM->PlayerRespawn(PlayerController);
	}

	BBComp->SetValueAsBool(bIsTouchingTarget.SelectedKeyName, false);
	return EBTNodeResult::Succeeded;
}
