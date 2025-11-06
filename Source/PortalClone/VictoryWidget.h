// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VictoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class PORTALCLONE_API UVictoryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	class UButton* ButtonRestart;

	UPROPERTY(meta=(BindWidget))
	class UButton* ButtonQuit;

private:
	UFUNCTION()
	void RestartGame();

	UFUNCTION()
	void QuitGame();
};
