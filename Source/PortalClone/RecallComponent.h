// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FRecallCircularBuffer.h"
#include "Components/ActorComponent.h"
#include "RecallComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTALCLONE_API URecallComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URecallComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:

	FTimerHandle TimerHandle;
	float IntervalTime =0.10f;
	float PosThresCm = 5.0f;
	float RotThresDegree = 3.0f;
	bool bRecalling;

	FVector LastPosition;
	FQuat LastRotation;
	int IndexFromNewest;
	
	FRecallCircularBuffer RecallCircularBuffer{10};

	void RecordObject();
	void StartRecall();
	void Recalling();
	void StopRecall();
	
};
