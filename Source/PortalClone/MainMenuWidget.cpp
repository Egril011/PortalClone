// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0))
	{
		//Show the mouse
		PlayerController->bShowMouseCursor = true;

		//Set the UI input
		FInputModeUIOnly InputModeUIOnly;
		InputModeUIOnly.SetWidgetToFocus(TakeWidget());
		InputModeUIOnly.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputModeUIOnly);
	}

	if (ButtonStart)
		ButtonStart->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::StartGame);

	if (ButtonQuit)
		ButtonQuit->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::QuitGame);
}

void UMainMenuWidget::StartGame()
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this,0))
	{
		//return the normal input
		PlayerController->bShowMouseCursor = false;
		FInputModeGameOnly InputModeGameOnly;
		PlayerController->SetInputMode(InputModeGameOnly);
	}
	
	UGameplayStatics::OpenLevel(this, TEXT("AbilityLevel"));
}

void UMainMenuWidget::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}
