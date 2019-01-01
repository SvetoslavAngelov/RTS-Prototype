// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MouseScrollDirection.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EMouseScrollDirection : uint8
{
	Centre UMETA(DisplayName = "Centre"),
	Left UMETA(DisplaName = "Left"),
	Right UMETA(DisplaName = "Right"),
	Top UMETA(DisplaName = "Top"),
	Bottom UMETA(DisplaName = "Bottom"),
	TopLeft UMETA(DisplaName = "TopLeft"),
	TopRight UMETA(DisplaName = "TopRight"),
	BottomLeft UMETA(DisplaName = "BottomLeft"),
	BottomRight UMETA(DisplaName = "BottomRight")
};