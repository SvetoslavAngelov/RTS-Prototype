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

	// Constructor from float
	FSelectionBox(float PointAX, float PointAY, float PointBX, float PointBY);

	// Constructor from FVector2D
	FSelectionBox(FVector2D const& PointA, FVector2D const& PointB);

	// Restore original values
	void Reset();

	// Data members
	UPROPERTY()
	FVector2D PointA; 

	UPROPERTY()
	FVector2D PointB;
};
