// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ColliderEndGame.generated.h"

class UVictoryWidget;
class UBoxComponent;

UCLASS()
class PORTALCLONE_API AColliderEndGame : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AColliderEndGame();

protected:
	UPROPERTY(EditAnywhere, Category="Collider")
	TObjectPtr<UBoxComponent> BoxColliderEndGame;

	UPROPERTY(EditAnywhere, Category = "WidgetEnd")
	TSubclassOf<UVictoryWidget> EndWidget;

private:
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
