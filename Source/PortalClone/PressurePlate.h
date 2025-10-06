// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "EPressurePlateTriggerType.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collider")
	UBoxComponent* BoxCollision;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY(EditAnywhere, Category="PressurePlate")
	TObjectPtr<ADoorPressedPlate> DoorPressedPlate = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PressurePlate")
	EPressurePlateTriggerType TriggerType;

private: 
	bool bIsActivate;
	TObjectPtr<URecallComponent> RecallComponent = nullptr;

	//Toggle the plate's colour and the door
	void TogglePlate(bool bActivate);

	//See which actor can trigger the pressure plate
	bool CanTriggerBy(AActor* Actor) const;

	UFUNCTION()
	void HandleRecallObject();
};


