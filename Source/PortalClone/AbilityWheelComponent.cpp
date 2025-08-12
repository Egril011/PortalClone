// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityWheelComponent.h"

#include "AbilityWheelWidget.h"
#include "PortalCloneGun.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UAbilityWheelComponent::UAbilityWheelComponent()
{

}

void UAbilityWheelComponent::OnClicked()
{
	ToggleAbilityWheel();
}

void UAbilityWheelComponent::CreateAbilityWheel()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PC) return;
	
	AbilityWheelInstance= CreateWidget<UAbilityWheelWidget>(PC, AbilityWheelClass);
	
	if (AbilityWheelInstance)
	{
		AbilityWheelInstance->OnRequestClose.AddDynamic(this, &UAbilityWheelComponent::OnClicked);
		AbilityWheelInstance->AddToViewport();
		AbilityWheelInstance->SetKeyboardFocus();
	}
}

void UAbilityWheelComponent::ToggleAbilityWheel()
{
	if (AbilityWheelInstance && AbilityWheelInstance->IsInViewport())
	{
		//Remove the Widget & BroadCast
		AbilityWheelInstance->OnRequestClose.RemoveDynamic(this, &UAbilityWheelComponent::OnClicked);
		AbilityWheelInstance->RemoveFromParent();
		AbilityWheelInstance = nullptr;

		//Get the player to allow them to move again and the camera too
		if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(),0))
		{
			PC->SetInputMode(FInputModeGameOnly());
			PC->bShowMouseCursor = false;

			PC->SetIgnoreLookInput(false);
			PC->SetIgnoreMoveInput(false);

			if (APortalCloneCharacter* Character = Cast<APortalCloneCharacter>(PC->GetPawn()))
			{
				Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
			}
		}
	}
	else
	{
		CreateAbilityWheel();
	}
}