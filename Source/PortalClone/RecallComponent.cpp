// Fill out your copyright notice in the Description page of Project Settings.


#include "RecallComponent.h"

// Sets default values for this component's properties
URecallComponent::URecallComponent() : RecallSpeed(1), bRecalling(false), LastPosition(), LastRotation(),
                                       IndexFromNewest(0),
                                       IndexFromOlder(0),
                                       RecallDeltaTimeAcc(0), RecallCircularBuffer(250)
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

	//Start the timer
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
	}
}

void URecallComponent::StartRecall()
{
	if (RecallCircularBuffer.GetSize() < 2)
	{
		StopRecall();
		return;
	}

	if (bRecalling)
		return;
	
	bRecalling = true;
	IndexFromNewest = 0;
	IndexFromOlder  = 1;
	RecallDeltaTimeAcc = 0.f;

	GetWorld()->GetTimerManager().PauseTimer(TimerHandle);

	//Remove the physic and the gravity from the object
	if (UPrimitiveComponent* Root = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()))
	{
		if (Root->IsAnySimulatingPhysics())
			Root->SetSimulatePhysics(false);

		Root->SetEnableGravity(false);
		Root->SetPhysicsLinearVelocity(FVector::ZeroVector);
		Root->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	}
}

void URecallComponent::Recalling(const float DeltaTime)
{
	if (!bRecalling)
		return;
	
	RecallDeltaTimeAcc -= DeltaTime * RecallSpeed;
	
	while (true)
	{
		// A = Newest & B = older
		FVector PositionA, PositionB;
		FQuat RotationA, RotationB;
		float TimeSecondsA, TimeSecondsB;

		// Search the information if they exist
		if (!RecallCircularBuffer.GetNewest(IndexFromNewest, PositionA, RotationA, TimeSecondsA) ||
			!RecallCircularBuffer.GetNewest(IndexFromOlder, PositionB, RotationB, TimeSecondsB))
		{
			StopRecall();
			return;
		}

		float TimeDuration = TimeSecondsA - TimeSecondsB;

		// make sure TimeDuration is grater than 0.0001
		if (TimeDuration <= KINDA_SMALL_NUMBER)
		{
			IndexFromNewest++;
			IndexFromOlder++;
			continue;
		}
		
		float TargetTime = TimeSecondsA + RecallDeltaTimeAcc;

		if (TargetTime >= TimeSecondsB && TargetTime <= TimeSecondsA)
		{
			float Alpha = (TargetTime - TimeSecondsB) / TimeDuration;

			FVector NewPosition = FMath::Lerp(PositionB, PositionA, Alpha);
			FQuat NewRotation = FQuat::Slerp(RotationB, RotationA, Alpha).GetNormalized();

			GetOwner()->SetActorLocationAndRotation(NewPosition, NewRotation, false, nullptr, ETeleportType::TeleportPhysics);
			break;
		}

		if (TargetTime < TimeSecondsB)
		{
			RecallDeltaTimeAcc += TimeDuration; 
			IndexFromNewest++;
			IndexFromOlder++;

			if (IndexFromOlder >= RecallCircularBuffer.GetSize())
			{
				GetOwner()->SetActorLocationAndRotation(PositionB, RotationB,
					false, nullptr, ETeleportType::None);
				
				StopRecall();
				return;
			}
			continue;
		}

		if (TargetTime > TimeSecondsA)
		{
			GetOwner()->SetActorLocationAndRotation(PositionA, RotationA,
				false, nullptr, ETeleportType::None);
			
			return;
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
	}

	GetWorld()->GetTimerManager().UnPauseTimer(TimerHandle);
	OnRecallFinished.Broadcast();
	RecallCircularBuffer.Clear();
}

