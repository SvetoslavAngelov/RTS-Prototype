// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SelectionBox.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FSelectionBox {
	GENERATED_USTRUCT_BODY()

	// Default constructor
	FSelectionBox();

	// Restore original values
	void Reset();

	UPROPERTY()
	FVector2D PointA; 

	UPROPERTY()
	FVector2D PointB;
};
