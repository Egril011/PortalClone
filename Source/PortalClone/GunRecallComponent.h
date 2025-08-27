// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GunRecallComponent.generated.h"

class URecallComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTALCLONE_API UGunRecallComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGunRecallComponent();

	void Recall(const FHitResult& HitResult);
	void CancelRecall();

private:
	UPROPERTY()
	TObjectPtr<AActor> ActorRef;

	UPROPERTY()
	TObjectPtr<URecallComponent> RecallComponent;
	
	bool bIsRecalling;

	UFUNCTION()
	void CleanUp();
};
