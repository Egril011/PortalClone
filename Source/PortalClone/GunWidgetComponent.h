// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GunWidgetComponent.generated.h"


class UGunStateWidget;
class UTrackGunStateComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTALCLONE_API UGunWidgetComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UGunWidgetComponent();
	
	//Initialize the Widget (Create the widget)
	void InitializeWidget(UTrackGunStateComponent* TrackGunStateComponent);

	//Destroy the Widget
	virtual void DestroyComponent(bool bPromoteChildren = false) override;
private:
	//The Widget for the Gun
	UPROPERTY(EditAnywhere, Category="GunWidget", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UUserWidget> GunWidget;

	TObjectPtr<UGunStateWidget> UserWidgetInstance;
};
