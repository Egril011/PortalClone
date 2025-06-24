// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "PortalCloneCharacter.h"
#include "GameFramework/Actor.h"
#include "TeleportationCapsule.generated.h"

UCLASS()
class PORTALCLONE_API ATeleportationCapsule : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleportationCapsule();

public:	
	//Play the animation to open the door
	void OpenDoor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimSequence* AnimOpenDoor;
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	//UAnimSequence* AnimCloseDoor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skeleton")
	USkeletalMeshComponent* SkeletonMeshCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skeleton")
	USkeletalMeshComponent* SkeletonMeshDoor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collider")
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleportation")
	USceneComponent* SceneTeleportation;

	UFUNCTION()
	void OverLapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

private:
	
	FTimerHandle TimeHandleCloseDoor;
	
	//Play the animation to close the door
	//void CloseDoor();

	//Teleport the player 
	void PlayerTeleportation(APortalCloneCharacter* Player);
};
