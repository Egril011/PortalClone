// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableTriggerComponent.generated.h"

class USphereComponent;
class UWidgetComponent;
class UUserWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTALCLONE_API UInteractableTriggerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractableTriggerComponent();

protected:
	virtual void OnRegister() override;
	
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
 
	UFUNCTION()
	void OverlapEnd(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> TriggerKeyWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Trigger", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USphereComponent> TriggerSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Trigger", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UWidgetComponent> WidgetComponent;
};
