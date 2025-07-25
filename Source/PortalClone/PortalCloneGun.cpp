// Fill out your copyright notice in the Description page of Project Settings.
#include "PortalCloneGun.h"
#include "PortalCloneCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "UObject/UnrealType.h"        
#include "UObject/Class.h"     
#include "UObject/ObjectMacros.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/PropertyAccessUtil.h"
#include "GunFireComponent.h"
#include "GunGrabComponent.h"
#include "TrackGunStateComponent.h"
#include "GunVFXComponent.h"

// Sets default values
APortalCloneGun::APortalCloneGun()
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(true);

	//Set the Muzzle scene to the original
	GunSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	RootComponent = GunSkeletalMesh;

	MuzzleSceneGrabbedObject = CreateDefaultSubobject<USceneComponent>(TEXT("SceneGrab"));
	MuzzleSceneGrabbedObject->SetupAttachment(GunSkeletalMesh);

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetupAttachment(GunSkeletalMesh);

	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &APortalCloneGun::OnOverlapBegin);

	//Components
	GunFireComponent = CreateDefaultSubobject<UGunFireComponent>(TEXT("GunFireComponent"));
	GunGrabComponent = CreateDefaultSubobject<UGunGrabComponent>(TEXT("GunGrabComponent"));
	TrackGunAbility = CreateDefaultSubobject<UTrackGunStateComponent>(TEXT("TrackGunAbility"));
	GunVFXComponent = CreateDefaultSubobject<UGunVFXComponent>(TEXT("GunVFXComponent"));
}

void APortalCloneGun::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) {

	if (OtherActor && OtherActor != this) {

		if (OtherActor->IsA(APortalCloneCharacter::StaticClass())) {

			APortalCloneCharacter* Player = Cast<APortalCloneCharacter>(OtherActor);

			if (Player) {
				
				AttachWeapon(Player);

				//remove the collider 
				SphereCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				SphereCollider->OnComponentBeginOverlap.RemoveDynamic(this, &APortalCloneGun::OnOverlapBegin);
			}
		}
	}
}

void APortalCloneGun::AttachWeapon(APortalCloneCharacter* TargetCharacter) {

	Character = TargetCharacter;

	if (Character) {
		
		AttachToComponent(Character->GetMesh1P(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("GripPoint"));
		SetOwner(Character);

		if (UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance())
		{
			// Set the HasRiffle variable
			FProperty* Prop = AnimInstance->GetClass()->FindPropertyByName(TEXT("HasRifle"));
			
			if (Prop && Prop->IsA(FBoolProperty::StaticClass()))
			{
				FBoolProperty* BoolProp = CastField<FBoolProperty>(Prop);
				BoolProp->SetPropertyValue_InContainer(AnimInstance, true);
			}
		}

		if(!bGunInputUnlocked)
		UnlockGunInput();
	}
}

void APortalCloneGun::UnlockGunInput() {

	if (bGunInputUnlocked || !Character) return;
	bGunInputUnlocked = true;

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
			EnhancedInputComponent->BindAction(FireEffectAction,
				ETriggerEvent::Triggered,
				GunFireComponent,
				&UGunFireComponent::FireEffect);

			EnhancedInputComponent->BindAction(GrabObjectAction, 
				ETriggerEvent::Started, 
				GunGrabComponent, 
				&UGunGrabComponent::GrabObject);

			OnShootVFX.AddDynamic(GunVFXComponent, &UGunVFXComponent::ShootEffect);

			EnhancedInputComponent->BindAction(ChangeGunStateAction, 
				ETriggerEvent::Started, 
				TrackGunAbility, 
				&UTrackGunStateComponent::ChangeGunEffect);
		}
	}
}