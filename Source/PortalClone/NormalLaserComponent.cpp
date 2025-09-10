// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalLaserComponent.h"

#include <ThirdParty/ShaderConductor/ShaderConductor/External/DirectXShaderCompiler/include/dxc/DXIL/DxilConstants.h>

void UNormalLaserComponent::FireLaser()
{
	FVector OwnerLocation = GetOwner()->GetActorLocation();
	FVector TargetLocation = TargetActor->GetActorLocation();

	DrawDebugLine(
		GetWorld(),
		OwnerLocation,
		TargetLocation,
		FColor::Cyan,
		false,
		0,
		2.f);
}

void UNormalLaserComponent::StartLaser(AActor* TargetActor)
{
	//Save the variable and set the Timer to fire the laser
	if (!TargetActor)
		SetLaserSuccess(false);

	this->TargetActor = TargetActor;

	GetWorld()->GetTimerManager().SetTimer(
		TimerHandleLaser,
		this,
		&UNormalLaserComponent::FireLaser,
		TimerTime,
		false
		);
}
