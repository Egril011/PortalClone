// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FreezableInterface.h"
#include "GameFramework/Actor.h"
#include "PressableInterface.h"
#include "RecallableInterface.h"
#include "NormalCube.generated.h"

class ACubeRespawn;
class UWidgetComponent;
class UFreezeComponent;
class UGunFreezeComponent;
class URecallComponent;

UCLASS()
class PORTALCLONE_API ANormalCube : public AActor, public IPressableInterface, public IRecallableInterface,
public IFreezableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANormalCube();

	//safe the cube respawn to respawn it if need it
	TObjectPtr<ACubeRespawn> Respawn;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StaticMesh")
	UStaticMeshComponent* StaticMesh;

	//Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	URecallComponent* RecallComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UFreezeComponent> FreezeComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Widget")
	TObjectPtr<UWidgetComponent> WidgetComponent;
	
	virtual void OnPlatePressed_Implementation() override;
	virtual void Recallable_Implementation() override;
	virtual void CancelRecall_Implementation() override;
	virtual void ApplyFreezeEffect_Implementation() override;

	//if the object goes out off bound because of the grab and throw
	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;
};