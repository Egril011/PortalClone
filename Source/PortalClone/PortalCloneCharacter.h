// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "PortalCloneCharacter.generated.h"

class UMenu;
class UWidgetComponent;
class UInputComponent;
class APortalCloneGun;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class APortalCloneCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APortalCloneCharacter();

	UPROPERTY(BlueprintReadOnly, Category = EqippedGun)
	TObjectPtr<APortalCloneGun> EquippedGun;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLookAtInteraction, bool, bIsLooking);
	FOnLookAtInteraction OnLookAtInteraction;

	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UPROPERTY(EditDefaultsOnly, Category = Movement, meta=(AllowPrivateAccess))
	float SprintSpeed = 1000.0f;
	
protected:
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	/** First-person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	//** Sprint Input action *//
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShowMenuAction;

	//** Sprint value *//
	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float NormalSpeed;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	
	// APawn interface
	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	UPROPERTY(EditAnywhere, Category="Interaction", meta=(AllowPrivateAccess))
	float InteractDistance = 500.f;
	
	//** Sprint function *//
	void Sprint();
	void StopSprinting();

	//method to interact with objects
	void CheckInteractable();

	//method to create the menu widget
	UFUNCTION()
	void CreateMenu();
	
	UPROPERTY(EditAnywhere, Category="Widget", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UMenu> MenuWidget;
	TObjectPtr<UMenu> MenuInstance;
	
	//Update the Widget between the crosshair and the interact UI
	void UpdateInteractableWidget();

	
	
private:
	//Save the current look at
	TObjectPtr<AActor> CurrentLookAtActor = nullptr;
	float TimeSinceLastTrace = 0;
};

