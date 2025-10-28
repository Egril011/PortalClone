// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProgressBarInterface.h"
#include "Components/ActorComponent.h"
#include "FreezeComponent.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndFreeze);
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PORTALCLONE_API UFreezeComponent : public UActorComponent, public IProgressBarInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFreezeComponent();
	void StartFreezeEffect();
	bool IsFrozen() const {return bFrozen;}

	//Cancels the freeze effect if the player reuse the freeze ability on already frozen object
	void CancelFreezeEffect();

	//To know when the freeze is done
	UPROPERTY()
	FOnEndFreeze OnEndFreeze;
	
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
	float Duration = 5.0f;
	
	/*Method*/
	void FreezeTimer();
	void SetFreezeState(bool State);
	
	virtual FOnProgressBarChange* GetProgressBarDelegation() override;
};
