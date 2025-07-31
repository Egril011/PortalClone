// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityWheelWidget.h"

#include <ThirdParty/ShaderConductor/ShaderConductor/External/DirectXShaderCompiler/include/dxc/DXIL/DxilConstants.h>

#include "PortalCloneCharacter.h"
#include "PortalCloneGun.h"
#include "TrackGunStateComponent.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UAbilityWheelWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		PlayerController->bShowMouseCursor = true;

		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		PlayerController->SetInputMode(InputMode);
	}
	
	if (AbilityFreeze)
	{
		AbilityFreeze->OnClicked.AddDynamic(this, &UAbilityWheelWidget::OnFreezeClicked);
	}

	if (AbilityGrab)
	{
		AbilityGrab->OnClicked.AddDynamic(this, &UAbilityWheelWidget::OnGrabClicked);
	}

	if (AbilityRecall)
	{
		AbilityRecall->OnClicked.AddDynamic(this, &UAbilityWheelWidget::OnRecallClicked) ;
	}
}

void UAbilityWheelWidget::OnFreezeClicked()
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		if (APortalCloneCharacter* CharacterRef = Cast<APortalCloneCharacter>(PlayerController->GetPawn()))
		{
			GunStateComponent = CharacterRef->EquippedGun->TrackGunAbility;
			if (GunStateComponent)
			{
				GunStateComponent->ChangeGunState(EGunStateHandler::Freeze);

				PlayerController->bShowMouseCursor = false;

				PlayerController->SetInputMode(FInputModeGameOnly());
			}
		}
	}
}

void UAbilityWheelWidget::OnGrabClicked()
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		if (APortalCloneCharacter* CharacterRef = Cast<APortalCloneCharacter>(PlayerController->GetPawn()))
		{
			GunStateComponent = CharacterRef->EquippedGun->TrackGunAbility;
			if (GunStateComponent)
			{
				GunStateComponent->ChangeGunState(EGunStateHandler::Grab);

				PlayerController->bShowMouseCursor = false;

				PlayerController->SetInputMode(FInputModeGameOnly());
			}
		}
	}
}

void UAbilityWheelWidget::OnRecallClicked()
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		if (APortalCloneCharacter* CharacterRef = Cast<APortalCloneCharacter>(PlayerController->GetPawn()))
		{
			GunStateComponent = CharacterRef->EquippedGun->TrackGunAbility;
			if (GunStateComponent)
			{
				GunStateComponent->ChangeGunState(EGunStateHandler::Recall);

				PlayerController->bShowMouseCursor = false;

				PlayerController->SetInputMode(FInputModeGameOnly());
			}
		}
	}
}