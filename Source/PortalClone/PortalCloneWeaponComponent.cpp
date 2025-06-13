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


UPortalCloneWeaponComponent::UPortalCloneWeaponComponent() {

	//Set the Muzzle scene to the original
	MuzzleSceneGrabbedObject = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleGrappedObject"));
	MuzzleSceneGrabbedObject->SetupAttachment(this, MuzzleSocketName);
}

void UPortalCloneWeaponComponent::BeginPlay() {
	
	Super::BeginPlay();

	if (!PhysicsHandle)
	{
		PhysicsHandle = NewObject<UPhysicsHandleComponent>(this, UPhysicsHandleComponent::StaticClass(), TEXT("GrabHandle"));
		if (PhysicsHandle)
		{
			PhysicsHandle->RegisterComponent();
		}
	}

	PrimaryComponentTick.bCanEverTick = true;
	SetComponentTickEnabled(false);
}

void UPortalCloneWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
		
	if (PhysicsHandle && PhysicsHandle->GrabbedComponent) {
		
		//change the object's location so that the location is always the same even though the object is far aways 
		FVector ObjectLocation = MuzzleSceneGrabbedObject->GetComponentLocation() + 
		(MuzzleSceneGrabbedObject->GetComponentRotation().Vector() * 250.0f);
		
		PhysicsHandle->SetTargetLocation(ObjectLocation);
	}
}

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
			EnhancedInputComponent->BindAction(GrabObjectAction, ETriggerEvent::Started, this, &UPortalCloneWeaponComponent::GrabObject);
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
	
	if (PhysicsHandle->GrabbedComponent) {
		ThrowObject();
		return;
	}

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
void UPortalCloneWeaponComponent::GrabObject() {

	if (PhysicsHandle->GrabbedComponent) {
		
		DropObject();
	}
	else {

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

			Primitive = HitResult.GetComponent();

			if (Primitive && Primitive->IsSimulatingPhysics()) {

				Primitive->SetSimulatePhysics(true);

				//Grap the object by using the physicsHandle 
				PhysicsHandle->GrabComponentAtLocationWithRotation(
					Primitive,
					NAME_None,
					Primitive->GetComponentLocation(),
					Primitive->GetComponentRotation()
				);

				Primitive->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

				SetComponentTickEnabled(true);
			}
		}
	}
}

//Method to allow the player to drop the object
void UPortalCloneWeaponComponent::DropObject() {

	if (PhysicsHandle && PhysicsHandle->GrabbedComponent) {

		//Reactive the collision with the player
		Primitive->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
		
		PhysicsHandle->ReleaseComponent();

		SetComponentTickEnabled(false);
	}
}

//Method to throw the object that the player's grabbing
void UPortalCloneWeaponComponent::ThrowObject() {

	PhysicsHandle->ReleaseComponent();

	Primitive->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);

	Primitive->AddImpulse(GetSocketRotation(MuzzleSocketName).Vector() * 1000.f * Primitive->GetMass(), NAME_None, false);
}