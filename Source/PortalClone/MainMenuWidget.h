// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "MainMenuWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class PORTALCLONE_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonStart;

	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonQuit;

private:
	//Open the level
	UFUNCTION()
	void StartGame();

	//Quit the Game
	UFUNCTION()
	void QuitGame();
};
