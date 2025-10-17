// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatformPlayerOnRecall.h"

#include "PortalCloneCharacter.h"
#include "RecallComponent.h"
#include "Components/BoxComponent.h"
#include "Widgets/Text/STextScroller.h"

AMovingPlatformPlayerOnRecall::AMovingPlatformPlayerOnRecall()
{
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(SkeletalMesh);

	RecallComponent = CreateDefaultSubobject<URecallComponent>(TEXT("RecallComponent"));

	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AMovingPlatformPlayerOnRecall::OnOverlapBegin);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &AMovingPlatformPlayerOnRecall::OnOverlapEnd);
}

void AMovingPlatformPlayerOnRecall::BeginPlay()
{
	Super::BeginPlay();
	EndPointLocation = EndPoint->GetComponentLocation();
	StartLocation = StartPoint->GetComponentLocation();
}

void AMovingPlatformPlayerOnRecall::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor) || OtherActor == this)
		return;

	if (OtherActor->IsA<APortalCloneCharacter>())
	{
		bPlayerIsOnPlatform = true;
		bReachedTarget = false;
		TargetLocation = EndPointLocation;
	}
}

void AMovingPlatformPlayerOnRecall::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!IsValid(OtherActor) || OtherActor == this)
		return;

	if (OtherActor->IsA<APortalCloneCharacter>())
	{
		if (bReachedTarget)
			return;
		
		TargetLocation = StartLocation;
	}
}

void AMovingPlatformPlayerOnRecall::UpdateMovingPlatform(float DeltaTime)
{	
	if (bReachedTarget || !bPlayerIsOnPlatform)
		return;
	
	//Move the Actor to the end point
	FVector ToTarget = TargetLocation - GetActorLocation();
	FVector Direction = ToTarget.GetSafeNormal();
	FVector NewActorLocation = GetActorLocation() + (Direction * MoveSpeed * DeltaTime);
	SetActorLocation(NewActorLocation);

	if (FVector::Dist(NewActorLocation, TargetLocation) < 1.0f )
	{
		bReachedTarget = true;
	}
}

void AMovingPlatformPlayerOnRecall::Recallable_Implementation()
{
	if (!IsValid(RecallComponent))
		return;
	
	RecallComponent->StartRecall();
}

void AMovingPlatformPlayerOnRecall::CancelRecall_Implementation()
{
	if (!IsValid(RecallComponent))
		return;

	RecallComponent->StopRecall();
}
