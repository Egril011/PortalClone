// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoundProgressBarWidget.generated.h"

class IProgressBarInterface;
class UImage;
class UWidgetComponent;

UCLASS()
class PORTALCLONE_API URoundProgressBarWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void InitializeOwner(UObject* Owner);
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ProgressBarImage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UMaterialInterface> BaseMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UMaterialInstanceDynamic> DynamicMaterial;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UI", meta = (AllowPrivateAccess))
	FName PercentageKeyName;

	UFUNCTION()
	void SetPercentage(float percentage);

	TObjectPtr<AActor> OwnerActor = nullptr;

	UPROPERTY()
	TScriptInterface<IProgressBarInterface> ProgressBarScript = nullptr;
};
