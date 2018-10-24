// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SelectionBoxDisplay.generated.h"

/**
 * 
 */
UCLASS()
class STRATEGYAFTERNOON_API ASelectionBoxDisplay : public AHUD
{
	GENERATED_BODY()

public: 
	// Default constructor
	ASelectionBoxDisplay();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame to display the selection box to screen
	virtual void DrawHUD() override; 

	// Draws each indivual line of the selection box
	void DrawSelectionBox();

	// Fills the selection box with a specified colour 
	void FillSelectionBox();

private: 
	// Pointer to the selection box as defined in StrategyPlayerController.h
	struct FSelectionBox const* SelectionBox; 

	// Colour of the selection box outline
	UPROPERTY()
	FColor OutlineColour; 

	// Selection box fill colour
	UPROPERTY()
	FLinearColor FillColour;

	// Thickness of the selection box in pixels
	UPROPERTY()
	float SelectionBoxThickness; 
};
