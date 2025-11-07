// Fill out your copyright notice in the Description page of Project Settings.


#include "VictoryWidget.h"

#include "MyGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UVictoryWidget::NativeConstruct()
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
	
	if (ButtonRestart)
		ButtonRestart->OnClicked.AddUniqueDynamic(this, &UVictoryWidget::RestartGame);

	if (ButtonQuit)
		ButtonQuit->OnClicked.AddUniqueDynamic(this, &UVictoryWidget::QuitGame);
}

void UVictoryWidget::RestartGame()
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this,0))
	{
		//return the normal input
		PlayerController->bShowMouseCursor = false;
		FInputModeGameOnly InputModeGameOnly;
		PlayerController->SetInputMode(InputModeGameOnly);
	}

	//Reset the abilities
	if (UMyGameInstance* MyGI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(this)))
	{
		MyGI->ResetAbilities();
	}
	
	UGameplayStatics::OpenLevel(this, TEXT("AbilityLevel"));
}

void UVictoryWidget::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}
