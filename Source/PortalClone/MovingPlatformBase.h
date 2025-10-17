// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FreezableInterface.h"
#include "GameFramework/Actor.h"
#include "MovingPlatformBase.generated.h"

class UFreezeComponent;
class UWidgetComponent;

UCLASS(Abstract)
class PORTALCLONE_API AMovingPlatformBase : public AActor, public IFreezableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatformBase();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void ApplyFreezeEffect_Implementation() override;

	// Every subclass defines its movement logic
	virtual void UpdateMovingPlatform(float Delta) PURE_VIRTUAL(AMovingPlatformBase::UpdateMovingPlatform);
	
	UPROPERTY(VisibleAnywhere, Category="Patform")
	TObjectPtr<UStaticMeshComponent> SkeletalMesh;

	UPROPERTY(VisibleAnywhere, Category = "Platform")
	TObjectPtr<USceneComponent> StartPoint;

	UPROPERTY(VisibleAnywhere, Category = "Platform")
	TObjectPtr<USceneComponent> EndPoint;

	UPROPERTY(VisibleAnywhere, Category="Platform|Widget")
	TObjectPtr<UWidgetComponent> WidgetComponent;

	UPROPERTY(VisibleAnywhere, Category="Platform|Component")
	TObjectPtr<UFreezeComponent> FreezeComponent;

	UPROPERTY(EditAnywhere, Category="Platform|Variable")
	float MoveSpeed = 200.0f;
};
