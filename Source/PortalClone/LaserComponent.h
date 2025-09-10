// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LaserComponent.generated.h"

class AAIController;
class UBehaviorTree;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFireFinished);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTALCLONE_API ULaserComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULaserComponent();
	
	UPROPERTY()
	FOnFireFinished OnFireFinished;
	
	virtual void StartLaser(AActor* TargetActor) PURE_VIRTUAL(ULaserComponent::StartLaser);
	virtual bool IsLaserSuccess() const {return bLaserSuccess;};
	
protected:
	virtual void FireLaser() PURE_VIRTUAL(ULaserComponent::FireLaser);
	virtual void SetLaserSuccess(bool bSuccess) {this->bLaserSuccess = bSuccess;};

private:
	bool bLaserSuccess;
};
