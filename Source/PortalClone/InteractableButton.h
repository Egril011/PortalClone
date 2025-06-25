// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "ActivatableInterface.h"
#include "InteractableButton.generated.h"

UCLASS()
class PORTALCLONE_API AInteractableButton : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableButton();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimSequence* PressAnimation;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "ActivatableTarget")
	AActor* ActivatableTarget;

private:
	virtual void Interact_Implementation() override;

	//Play the button animation
	void PlayAnimation();
};
