// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_FlyChasePlayer.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

UBTTaskNode_FlyChasePlayer::UBTTaskNode_FlyChasePlayer()
{
	NodeName = TEXT("Fly: Chase Target");
}

EBTNodeResult::Type UBTTaskNode_FlyChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BBComp = OwnerComp.GetBlackboardComponent();
	if (!IsValid(BBComp))
		return EBTNodeResult::Failed;

	AIController = OwnerComp.GetAIOwner();
	if (!IsValid(AIController))
		return EBTNodeResult::Failed;

	SelfPawn = AIController->GetPawn();
	if (!IsValid(SelfPawn))
		return EBTNodeResult::Failed;

	Target = Cast<AActor>(BBComp->GetValueAsObject(TargetActor.SelectedKeyName));
	if (!IsValid(Target))
		return EBTNodeResult::Failed;

	//Modify the Pawn speed (FloatingPawnMovement)
	if (UFloatingPawnMovement* MovementComp = Cast<UFloatingPawnMovement>(SelfPawn->GetMovementComponent()))
	{
		MovementComp->MaxSpeed = Speed;
	}
	
	bNotifyTick = true;
	return EBTNodeResult::InProgress;
}

void UBTTaskNode_FlyChasePlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	if (!IsValid(AIController) && !IsValid(BBComp))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	
	//Save the target's position
	BBComp->SetValueAsVector(LastTargetLocationKeyName.SelectedKeyName, Target->GetActorLocation());

	//AI Height
	FVector NewTargetLocation = Target->GetActorLocation() + FVector(0.f, 0.f,HeightAI);
	
	//Move the AI to the Target
	FVector ToTarget = NewTargetLocation - SelfPawn->GetActorLocation();
	FVector Direction = ToTarget.GetSafeNormal();
	SelfPawn->AddMovementInput(Direction, 1.f);

	//Make the AI look at the target
	FRotator LookRotation = ToTarget.Rotation();
	LookRotation.Pitch = 0.f;
	SelfPawn->SetActorRotation(FMath::RInterpTo(SelfPawn->GetActorRotation(), LookRotation, DeltaSeconds, 5.f));

	//Get the Distance between the pawn and the target
	if (ToTarget.Size() < AcceptanceRadius)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

		//tell the AI have touched the target
		BBComp->SetValueAsBool(bIsTouchingTarget.SelectedKeyName, true);
	}
}