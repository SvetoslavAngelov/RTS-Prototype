// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SelectionBox.h"
#include "StrategyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class STRATEGYAFTERNOON_API AStrategyPlayerController : public APlayerController
{
	GENERATED_BODY()

public: 
	// Default constructor
	AStrategyPlayerController(); 
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; 

	// Called every frame 
	virtual void Tick(float DeltaTime) override; 

	// Set up player input 
	virtual void SetupInputComponent() override; 

	// Mouse select interface
	void OnMousePressed(); 
	void OnMouseReleased();
	void DefineSelectionBox(); 

	// Camera movement interface 
	void MoveCamera(FVector2D const& MousePosition, FIntPoint const& ViewportSize) const;

	// Contains the coordinates of the mouse drag selection box
	UPROPERTY()
	FSelectionBox SelectionBox;

private: 
	// Pointer to the camera pawn 
	UPROPERTY()
	class ACameraPawn const* CameraPawn; 

	// Current view port size. 
	// NOTE: This is different from resolution
	UPROPERTY()
	FIntPoint ViewportSize; 

	// Checks if left mouse button is pressed 
	UPROPERTY()
	bool bIsSelected;

	// Checks if the selection box start coordinates have been initialized
	UPROPERTY()
	bool bIsVariableInitialized;
};

