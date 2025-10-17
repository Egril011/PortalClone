// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovingPlatformBase.h"
#include "RecallableInterface.h"
#include "MovingPlatformPlayerOnRecall.generated.h"

class URecallComponent;
class UBoxComponent;
/**
 * 
 */
UCLASS()
class PORTALCLONE_API AMovingPlatformPlayerOnRecall : public AMovingPlatformBase, public IRecallableInterface
{
	GENERATED_BODY()
public:
	AMovingPlatformPlayerOnRecall();
	
protected:
	UPROPERTY(VisibleAnywhere, Category="Platform|Component")
	TObjectPtr<URecallComponent> RecallComponent;
	
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCollider; 

	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void UpdateMovingPlatform(float DeltaTime) override;
	virtual void Recallable_Implementation() override;
	virtual void CancelRecall_Implementation() override;

private:
	bool bReachedTarget = false;
	bool bPlayerIsOnPlatform = false;
	FVector EndPointLocation;
	FVector StartLocation;
	FVector TargetLocation;
};
