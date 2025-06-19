// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimSequence* AnimCloseDoor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skeleton")
	USkeletalMeshComponent* SkeletonMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collider")
	UBoxComponent* BoxCollision;

private:
	
	FTimerHandle TimeHandleCloseDoor;
	
	//Play the animation to close the door
	void CloseDoor();


};
