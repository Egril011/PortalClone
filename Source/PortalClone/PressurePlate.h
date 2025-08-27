// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PressurePlate.generated.h"

class URecallComponent;
class ADoorPressedPlate;

UCLASS()
class PORTALCLONE_API APressurePlate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APressurePlate();

	virtual void BeginPlay() override;
	
	bool IsActivate() const { return bIsActivate; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skeleton")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	UMaterialInterface* ActivateColour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	UMaterialInterface* NoActivateColour;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collider")
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere)
	ADoorPressedPlate* DoorPressedPlate;

private: 
	bool bIsActivate;
	URecallComponent* RecallComponent;

	//Toggle the plate's colour and the door
	void TogglePlate(bool bActivate);

	UFUNCTION()
	void HandleRecallObject();
};


