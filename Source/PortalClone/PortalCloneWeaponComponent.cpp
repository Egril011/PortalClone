// Copyright Epic Games, Inc. All Rights Reserved.

#include "PortalCloneWeaponComponent.h"
#include "PortalCloneCharacter.h"
#include "PortalCloneProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Animation/AnimInstance.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "GunTimeStateHandler.h"

bool UPortalCloneWeaponComponent::AttachWeapon(APortalCloneCharacter* TargetCharacter)
{
	Character = TargetCharacter;

	// Check that the character is valid, and has no weapon component yet
	if (Character == nullptr || Character->GetInstanceComponents().FindItemByClass<UPortalCloneWeaponComponent>())
	{
		return false;
	}

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));

	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// FireEffect
			EnhancedInputComponent->BindAction(FireEffectAction, ETriggerEvent::Triggered, this, &UPortalCloneWeaponComponent::FireEffect);

			//Change gun's state
			EnhancedInputComponent->BindAction(ChangeGunStateAction, ETriggerEvent::Started, this, &UPortalCloneWeaponComponent::ChangeGunEffect);
			
			//Grab item and put it in front of the player
			EnhancedInputComponent->BindAction(GrabItemAction, ETriggerEvent::Started, this, &UPortalCloneWeaponComponent::GrabItem);
			
			//Drop the item that was in front of the player
			EnhancedInputComponent->BindAction(GrabItemAction, ETriggerEvent::Completed, this, &UPortalCloneWeaponComponent::DropItem);
		}
	}

	return true; 
}

void UPortalCloneWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// ensure we have a character owner
	if (Character != nullptr)
	{
		// remove the input mapping context from the Player Controller
		if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->RemoveMappingContext(FireMappingContext);
			}
		}
	}

	// maintain the EndPlay call chain
	Super::EndPlay(EndPlayReason);
}

//Method for the Fire Effect
void UPortalCloneWeaponComponent::FireEffect() {
	
	//Start the LineTrace
	FVector Start = GetSocketLocation(MuzzleSocketName);
	FVector ForwardVector = GetSocketRotation(MuzzleSocketName).Vector();
	FVector End = Start + (ForwardVector * 1000.0f);

	FHitResult HitResult;

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_Visibility
	);

	if (bHit) {
		
		AActor* HitActor = HitResult.GetActor();

		UMyGameInstance* GI = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());

		/*Debug*/
		if (GI->CurrentGunState == EGunTimeState::Slow) {
			DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 10.0f, 0, 1.0f);
		}
		else {
			DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 10.0f, 0, 1.0f);
		}

		//Call the method that will apply the state based on the gun's effect
		GunTimeStateHandler::ApplyState(HitActor, GI);
	}
}
 
//Toggles the gun's time effect between Slow and Speed
void UPortalCloneWeaponComponent::ChangeGunEffect() {

	UMyGameInstance* GI = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());

	if (!GI) 
	return;

	// Toggle between Slow and Speed effects
	if (GI->CurrentGunState == EGunTimeState::Slow) {
		
		GI->CurrentGunState = EGunTimeState::Speed;

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Speed mode"));
		}
	}
	else {
		GI->CurrentGunState = EGunTimeState::Slow;

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Slow mode"));
		}
	}
}

//Method for the object goes in front of the player
void UPortalCloneWeaponComponent::GrabItem() {

	//Start the LineTrace
	FVector Start = GetSocketLocation(MuzzleSocketName);
	FVector ForwardVector = GetSocketRotation(MuzzleSocketName).Vector();
	FVector End = Start + (ForwardVector * 1000.0f);

	FHitResult HitResult;

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_Visibility
	);

	if (bHit) {        

		/*Debug*/
		DrawDebugLine(GetWorld(), Start, End, FColor::Yellow, false, 10.0f, 0, 1.0f);

		UPrimitiveComponent* Primitive = HitResult.GetComponent();

		if (Primitive && Primitive->IsSimulatingPhysics()) {

			Primitive->SetSimulatePhysics(false);

			//calculate the distance from where the item will be form the player
			float DistanceMuzzle = 200.0f;
			FVector LocationMuzzle = Start + (ForwardVector * DistanceMuzzle);
			Primitive->SetWorldLocation(LocationMuzzle);

			//attache the item to the parent (gun's socket)
			Primitive->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform,
			MuzzleSocketName);
		}
	}
}

void UPortalCloneWeaponComponent::DropItem() {

}