// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneAIController.h"

#include "DroneAIPawn.h"
#include "LaserComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
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
	if(!IsValid(DronePerceptionComponent))
		return;
	
	DronePerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(
		this, &ADroneAIController::OnTargetPerceptionUpdated);
}

void ADroneAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	ADroneAIPawn* AIDronePawn = Cast<ADroneAIPawn>(InPawn);
	if (!AIDronePawn)
		return;
	
	UBlackboardComponent* BB = nullptr;
	if (!UseBlackboard(DroneBehaviorTree->BlackboardAsset, BB))
	{
		UE_LOG(LogTemp, Warning, TEXT("Null"));
		return;
	}

	ULaserComponent* LaserComponent = AIDronePawn->GetCurrentLaserComponent();
	if (!LaserComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("No LaserComponent found!"));
		return;
	}

	const FName LaserKey = TEXT("CurrentLaserCompKey");
	BB->SetValueAsObject(LaserKey,LaserComponent);

	if (DroneBehaviorTree)
	{
		RunBehaviorTree(DroneBehaviorTree);
	}
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
	
	if (Stimulus.WasSuccessfullySensed() && Actor == Player)
	{
		BB->SetValueAsObject(TargetKeyName, Player);
	}
	else
	{
		if (BB->GetValueAsObject(TargetKeyName) == Player)
		{
			BB->ClearValue(TargetKeyName);
		}
	}
}
