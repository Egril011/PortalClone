// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EDoorAnimation.h"
#include "DoorPressedPlate.generated.h"

class APressurePlate;

UCLASS()
class PORTALCLONE_API ADoorPressedPlate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorPressedPlate();

	//Check if the plates states changed
	void ArePlateChanged();
	

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkeletalMesh")
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere)
	TArray<APressurePlate*> RequiredPressurePlate;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimSequence* OpenDoorAnimation;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimSequence* CloseDoorAnimation;

private:
	
	//get the door state
	EDoorAnimation DoorState;

	//Check if all the plate are pressed
	bool AreAllPlatesActivated() const;

	//Play its animation (close the door)
	void PlayCloseDoor();

	//Play its animation (open the door)
	void PlayOpenDoor();
};