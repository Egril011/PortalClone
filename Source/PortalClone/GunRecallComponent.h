// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GunRecallComponent.generated.h"

class URecallVFXComponent;
class APortalCloneGun;
class URecallComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTALCLONE_API UGunRecallComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGunRecallComponent();

	void Recall(const FHitResult& HitResult);

	/*If the player has the gun and the recall ability on and right click*/
	void CancelRecall();

protected:
	UPROPERTY(EditAnywhere, Category = "RecallVFX")
	TObjectPtr<URecallVFXComponent> RecallVFXComponent;
	
private:
	UPROPERTY()
	TObjectPtr<AActor> ActorRef;

	UPROPERTY()
	TObjectPtr<URecallComponent> RecallComponent;
	
	bool bIsRecalling;

	/*CleanUp everything*/
	UFUNCTION()
	void CleanUp();
};
