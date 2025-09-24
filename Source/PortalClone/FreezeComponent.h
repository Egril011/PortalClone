// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProgressBarInterface.h"
#include "Components/ActorComponent.h"
#include "FreezeComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PORTALCLONE_API UFreezeComponent : public UActorComponent, public IProgressBarInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFreezeComponent();
	void StartFreezeEffect();
	bool IsFrozen() const {return bFrozen;}
	
private:
	TObjectPtr<AActor> Owner = nullptr;
	TObjectPtr<UStaticMeshComponent> SM = nullptr;
	bool bFrozen;
	bool bIsActorSimulatePhysics;
	
	UPROPERTY()
	FOnProgressBarChange OnProgressBarDelegate;
	
	/*Timer aspects*/
	FTimerHandle FreezeTimerHandle;
	float StartTime;

	UPROPERTY(EditAnywhere, Category = "FreezeComponent|Variable", meta = (AllowPrivateAccess = "true"))
	float Duration;
	
	/*Method*/
	void FreezeTimer();
	void SetFreezeState(bool State);
	
	virtual FOnProgressBarChange* GetProgressBarDelegation() override;
};
