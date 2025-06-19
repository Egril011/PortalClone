// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "TeleportationCapsule.h"
#include "ActivateCapsuleButton.generated.h"

UCLASS()
class PORTALCLONE_API AActivateCapsuleButton : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActivateCapsuleButton();


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimSequence* AnimSequence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleportation")
	ATeleportationCapsule* TeleportationCapsule;

private:
	virtual void Interact() override;

	//Play the button animation
	void PlayAnimation();
};
