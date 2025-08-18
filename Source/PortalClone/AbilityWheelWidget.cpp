// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityWheelWidget.h"

#include "PortalCloneCharacter.h"
#include "PortalCloneGun.h"
#include "TrackGunStateComponent.h"
#include "Components/Button.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void UAbilityWheelWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetIsFocusable(true);
	
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		PlayerController->bShowMouseCursor = true;

		//Set the input only for the Widget
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputMode);

		//stop the camera moving 
		PlayerController->SetIgnoreLookInput(true);
		PlayerController->SetIgnoreMoveInput(true);
		
		//Get the player to prevent it from moving and get a reference to TrackAbility
		if (APortalCloneCharacter* Character = Cast<APortalCloneCharacter>(PlayerController->GetPawn()))
		{
			Character->GetCharacterMovement()->DisableMovement();

			if (!Character->EquippedGun)
				return;

			if (Character->EquippedGun->IsA<APortalCloneGun>())
			{
				TrackGunAbility = Character->EquippedGun->TrackGunAbility;
			}
		}

		//show the buttons that the player has unlocked
		SetupAbility(AbilityFreeze,
			TrackGunAbility->CanFreezeObject(),
			FName("OnFreezeClicked"));

		SetupAbility(AbilityGrab,
			TrackGunAbility->CanGrabObject(),
			FName("OnGrabClicked"));

		SetupAbility(AbilityRecall,
			TrackGunAbility->CanRecallObject(),
			FName("OnRecallClicked"));
	}
}

FReply UAbilityWheelWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Q)
	{
		OnRequestClose.Broadcast();
		return FReply::Handled();
	}
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UAbilityWheelWidget::OnFreezeClicked()
{
	TrackGunAbility->ChangeGunState(EGunStateHandler::Freeze);
}

void UAbilityWheelWidget::OnGrabClicked()
{
	TrackGunAbility->ChangeGunState(EGunStateHandler::Grab);
}

void UAbilityWheelWidget::OnRecallClicked()
{
	TrackGunAbility->ChangeGunState(EGunStateHandler::Recall);
}

void UAbilityWheelWidget::SetupAbility(UButton* Button, const bool bIsUnlocked, const FName HandlerName)
{
	if (!Button)
		return;

	Button->SetVisibility(bIsUnlocked ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);

	if (bIsUnlocked)
	{
		Button->OnClicked.Clear();

		if (FindFunction(HandlerName))
		{
			FScriptDelegate Delegate;
			Delegate.BindUFunction(this, HandlerName);
			Button->OnClicked.Add(Delegate);
		}
	}
}
