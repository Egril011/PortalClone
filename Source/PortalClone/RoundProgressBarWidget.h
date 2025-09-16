// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoundProgressBarWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class PORTALCLONE_API URoundProgressBarWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void SetPercentage(float percentage) const;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UMaterialInterface> BaseMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UMaterialInstanceDynamic> DynamicMaterial;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UI", meta = (AllowPrivateAccess))
	FName PercentageKeyName;
};
