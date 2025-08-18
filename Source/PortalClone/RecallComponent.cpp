// Fill out your copyright notice in the Description page of Project Settings.


#include "RecallComponent.h"

#include "Constraint.h"
#include "Net/Core/Analytics/NetStatsUtils.h"

// Sets default values for this component's properties
URecallComponent::URecallComponent(): bRecalling(false), LastPosition(), LastRotation(), IndexFromNewest(0)
{
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void URecallComponent::BeginPlay()
{
	Super::BeginPlay();

	//Get the Actor's Location 
	LastPosition = GetOwner()->GetActorLocation();
	LastRotation = GetOwner()->GetActorQuat();

	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		this,
		&URecallComponent::RecordObject,
		IntervalTime,
		true);
}

void URecallComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bRecalling)
		Recalling(DeltaTime);
}


void URecallComponent::RecordObject()
{
	if (bRecalling)
		return;

	const FVector PositionSave = GetOwner()->GetActorLocation();
	const FQuat RotationSave = GetOwner()->GetActorQuat();

	//See if the Actor has moved and its position is greater than PosThresCm and RotThresDegree
	const bool bMoving = FVector::DistSquared(PositionSave, LastPosition) > FMath::Square(PosThresCm);
	const bool bRotating =  RotationSave.AngularDistance(LastRotation) > FMath::DegreesToRadians(RotThresDegree);

	if (bMoving || bRotating)
	{
		RecallCircularBuffer.Push_Head(PositionSave, RotationSave, GetWorld()->GetTimeSeconds());

		LastPosition = PositionSave;
		LastRotation = RotationSave;
		
		if (GEngine)
		{
			FString DebugMsg = FString::Printf(
				TEXT("Last Pos: %s  |  Last Rot: %s"),
				*LastPosition.ToString(),
				*LastRotation.ToString()
			);

			GEngine->AddOnScreenDebugMessage(
				-1,
				5.f,
				FColor::Red,
				DebugMsg
			);
		}
	}

}

void URecallComponent::StartRecall()
{
	if (RecallCircularBuffer.GetSize() < 2)
	{
		StopRecall();
		return;
	}
	
	IndexFromNewest = 0;
	RecallStepAcc = 0.0f;
	
	if (UPrimitiveComponent* Root = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()))
	{
		if (Root->IsAnySimulatingPhysics())
			Root->SetSimulatePhysics(false);

		Root->SetEnableGravity(false);
		Root->SetPhysicsLinearVelocity(FVector::ZeroVector);
		Root->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	}

	bRecalling = true;
}

void URecallComponent::Recalling(float DeltaTime)
{
	if (!bRecalling)
		return;

	RecallStepAcc += DeltaTime * 1;

	while (RecallStepAcc >= IntervalTime)
	{
		FVector Position;
		FQuat Rotation;
		float TimeSeconds;

		if (!RecallCircularBuffer.GetNewest(IndexFromNewest,Position, Rotation,TimeSeconds))
		{
			StopRecall();
			return;
		}

		GetOwner()->SetActorLocationAndRotation(Position, Rotation, false, nullptr, ETeleportType::TeleportPhysics);

		if (GEngine)
		{
			FString DebugMsg = FString::Printf(
				TEXT("New Pos: %s  |  new Rot: %s"),
				*Position.ToString(),
				*Rotation.ToString()
			);

			GEngine->AddOnScreenDebugMessage(
				-1,
				5.f,
				FColor::Red,
				DebugMsg
			);
		}

		IndexFromNewest++;
		RecallStepAcc -= IntervalTime;

		if (IndexFromNewest >= RecallCircularBuffer.GetSize())
		{
			StopRecall();
		}
	}
}

void URecallComponent::StopRecall()
{
	if (!bRecalling)
		return;

	bRecalling = false;

	if (UPrimitiveComponent* Root = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()))
	{
		Root->SetEnableGravity(true);
		Root->SetSimulatePhysics(true);

		GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Red, "StopRecall");
	}

	RecallCircularBuffer.Clear();
}

