   // Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMenu::NativeConstruct()
{
	Super::NativeConstruct();
	SetIsFocusable(true);

	//Pause the game 
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	
	//Set the button and their action
	ButtonExit->OnClicked.AddUniqueDynamic(this, &UMenu::OnClickExit);
}

FReply UMenu::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{	
	if (InKeyEvent.GetKey() == EKeys::Escape)
	{
		SetIsFocusable(false);
		UGameplayStatics::SetGamePaused(GetWorld(), false);

		OnRequestClose.Broadcast();
		return FReply::Handled();
	}
	
   return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UMenu::OnClickExit()
{
	
}
