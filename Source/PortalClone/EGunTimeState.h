// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class EGunTimeState : uint8
{
    None,
    Slow,
    Speed,
    Freeze
};