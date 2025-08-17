// Fill out your copyright notice in the Description page of Project Settings.


#include "RecallComponent.h"

#include "INodeAndChannelMappings.h"

// Sets default values for this component's properties
URecallComponent::URecallComponent(): bRecalling(false), LastPosition(), LastRotation(), IndexFromNewest(0)
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void URecallComponent::BeginPlay()
{
	Super::BeginPlay();

	//Get the Actor's Location 
	LastPosition = GetOwner()->GetActorLocation();
	LastRotation = GetOwner()->GetActorQuat();

	// Save it as first position
	RecallCircularBuffer.Push_Head(LastPosition, LastRotation, GetWorld()->GetTimeSeconds());

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
}

void URecallComponent::RecordObject()
{
	if (bRecalling)
		return;

	const FVector PositionSave = GetOwner()->GetActorLocation();
	const FQuat RotationSave = GetOwner()->GetActorQuat();

	//See if the Actor has moved and its position is greater than PosThresCm and RotThresDegree
	const bool bMoving = FVector::DistSquared(PositionSave, LastPosition) > PosThresCm;
	const bool bRotating =  RotationSave.AngularDistance(LastRotation) > RotThresDegree;

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
	
	bRecalling = true;
	
	if (UPrimitiveComponent* Root = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()))
	{
		if (Root->IsAnySimulatingPhysics())
			Root->SetSimulatePhysics(false);

		Root->SetEnableGravity(false);
		Root->SetPhysicsLinearVelocity(FVector::ZeroVector);
		Root->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	}
}

void URecallComponent::Recalling()
{
	FVector Postition;
	FQuat Rotation;
	float TimeSeconds;

	for (int i = 0; i < RecallCircularBuffer.GetSize(); i++)
	{
		if (!RecallCircularBuffer.GetNewest(i,Postition, Rotation,TimeSeconds))
		{
			StopRecall();
			return;
		}

		GetOwner()->SetActorLocationAndRotation(Postition, Rotation, false, nullptr, ETeleportType::TeleportPhysics);
	}
}

void URecallComponent::StopRecall()
{
	if (!bRecalling)
		return;

	bRecalling = false;

	if (UPrimitiveComponent* Root = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()))
	{
		if (Root->IsAnySimulatingPhysics())
			Root->SetSimulatePhysics(true);

		Root->SetEnableGravity(true);
	}
}

