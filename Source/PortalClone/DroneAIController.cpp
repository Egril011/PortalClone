// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "Microsoft/AllowMicrosoftPlatformTypes.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ADroneAIController::ADroneAIController()
{
	//Allow the Drone to see
	DronePerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Drone_Perception"));
	DronePerceptionSight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Drone_Sense"));
	if (!DronePerceptionComponent)
		return;

	DronePerceptionComponent->ConfigureSense(*DronePerceptionSight);
	DronePerceptionComponent->SetDominantSense(UAISense_Sight::StaticClass());
	SetPerceptionComponent(*DronePerceptionComponent);

	DronePerceptionSight->DetectionByAffiliation.bDetectNeutrals = true;
	DronePerceptionSight->DetectionByAffiliation.bDetectFriendlies = true;
	DronePerceptionSight->DetectionByAffiliation.bDetectEnemies = true;
}

void ADroneAIController::BeginPlay()
{
	Super::BeginPlay();
	check(DronePerceptionComponent);
	
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay: binding delegates"));
	DronePerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(
		this, &ADroneAIController::OnTargetPerceptionUpdated);
}

void ADroneAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (DroneBehaviorTree)
		RunBehaviorTree(DroneBehaviorTree);
}

void ADroneAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!Actor)
		return;

	UBlackboardComponent* BB = GetBlackboardComponent();

	if (!BB)
		return;

	APawn* Player = UGameplayStatics::GetPlayerPawn(this, 0);

	if (!Player)
		return;

	const FName TargetKey = TEXT("TargetActor");
	
	if (Stimulus.WasSuccessfullySensed() && Actor == Player)
	{
		BB->SetValueAsObject(TargetKey, Player);
	}
	else
	{
		if (BB->GetValueAsObject(TargetKey) == Player)
		{
			BB->ClearValue(TargetKey);
		}
	}
}
