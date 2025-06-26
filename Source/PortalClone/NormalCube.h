// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PressableInterface.h"
#include "NormalCube.generated.h"

UCLASS()
class PORTALCLONE_API ANormalCube : public AActor, public IPressableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANormalCube();
	
	void BeginPlay();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StaticMesh")
	UStaticMeshComponent* StaticMesh;

	virtual void OnPlatePressed_Implementation() override;
};
