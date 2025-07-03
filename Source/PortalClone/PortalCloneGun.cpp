// Fill out your copyright notice in the Description page of Project Settings.

#include "TrackGunAbility.h"
#include "PortalCloneCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "MyGameInstance.h"
#include "UObject/UnrealType.h"        
#include "UObject/Class.h"     
#include "UObject/ObjectMacros.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/PropertyAccessUtil.h"
#include "PortalCloneGun.h"

// Sets default values
APortalCloneGun::APortalCloneGun()
{
	//Set the Muzzle scene to the original
	GunSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	RootComponent = GunSkeletalMesh;

	MuzzleSceneGrabbedObject = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleScene"));
	MuzzleSceneGrabbedObject->SetupAttachment(GunSkeletalMesh);

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetupAttachment(GunSkeletalMesh);

	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &APortalCloneGun::OnOverlapBegin);
}

void APortalCloneGun::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) {

	if (OtherActor && OtherActor != this) {

		if (OtherActor->IsA(APortalCloneCharacter::StaticClass())) {

			APortalCloneCharacter* Player = Cast<APortalCloneCharacter>(OtherActor);

			if (Player) {
				
				AttachWeapon(Player);
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
	}
}