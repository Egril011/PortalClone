// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Materials/MaterialExpressionFloatToUInt.h"
#include "PatrolPoints.generated.h"

class UArrowComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTALCLONE_API APatrolPoints : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	APatrolPoints();

	//return the floor that belong to the point
	int GetFloorNumber() const { return FloorNumber; }

protected:
	TObjectPtr<UArrowComponent> ArrowComponent;

	UPROPERTY(EditAnywhere, Category = "PatrolPoints")
	int FloorNumber; 
};
