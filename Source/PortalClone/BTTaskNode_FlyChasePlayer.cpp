// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_FlyChasePlayer.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTTaskNode_FlyChasePlayer::UBTTaskNode_FlyChasePlayer()
{
	NodeName = TEXT("Fly: Chase Player");
}

EBTNodeResult::Type UBTTaskNode_FlyChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	bNotifyTick = true;
	return EBTNodeResult::InProgress;
}

void UBTTaskNode_FlyChasePlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (!IsValid(BBComp))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!IsValid(AIController))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	
	APawn* SelfPawn = AIController->GetPawn();
	if (!IsValid(SelfPawn))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	
	AActor* Player = Cast<AActor>(BBComp->GetValueAsObject(TargetActor.SelectedKeyName));
	if (!IsValid(Player))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	
	//Move the Ai to the Player
	FVector PlayerLocation = Player->GetActorLocation();
	FVector PawnLocation = SelfPawn->GetActorLocation();
	
	FVector TargetLocation = FVector(PlayerLocation.X, PlayerLocation.Y, PawnLocation.Z + ElevationHeight);
	
	FVector TargetDistance = TargetLocation - PawnLocation;
	float Distance = FVector(TargetDistance.X, TargetDistance.Y, 0.f).Size();

	if (Distance < AcceptanceRadius)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	FVector PawnDirection = FVector(TargetDistance.X, TargetDistance.Y, 0.f).GetSafeNormal();
	FVector Direction = PawnDirection * Speed * DeltaSeconds;
	
	SelfPawn->SetActorLocation(SelfPawn->GetActorLocation() + Direction, true);

	//Rotate the AI for he is looking to the player
	SelfPawn->SetActorRotation(Direction.Rotation());    
}
