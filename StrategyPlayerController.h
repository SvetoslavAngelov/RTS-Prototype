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

	/**
	* SELECTION INTERFACE
	*/
	// Sets the LMB flag
	void OnLMBPressed(); 
	void OnLMBReleased();

	// Sets the RMB flag and updates the new dispatch destination
	void OnRMBPressed(); 
	void OnRMBReleased();

	// Defines the dimensions of the selection box in screen space
	void DefineSelectionBox(); 

	// Defines the dimensions of the selection box in world space
	void DefineSelectionBoxToWorld();

	// Sets the selection box dimensions back to defaults (0)
	void SelectionBoxReset();

	// Camera movement interface 
	void MoveCamera() const;

	// Contains the coordinates of the mouse drag selection box
	UPROPERTY()
	FSelectionBox SelectionBox;

	// Containst the coordinates of the mouse drag selection box to world space 
	UPROPERTY()
	FSelectionBox SelectionBoxToWorld;

private: 
	// Pointer to the camera pawn 
	UPROPERTY()
	class ACameraPawn const* CameraPawn; 

	// Current view port size. 
	// NOTE: This is different from resolution
	UPROPERTY()
	FIntPoint ViewportSize; 

	// Holds the current mouse position
	UPROPERTY()
	FVector2D MousePosition;

	// Checks if left mouse button is pressed 
	UPROPERTY()
	bool bIsLMBPressed;

	// Checks if right mouse button is pressed
	UPROPERTY()
	bool bIsRMBPressed;

	// Checks if the selection box start coordinates have been initialized
	UPROPERTY()
	bool bIsSelectBoxInit;

	// Checks if the selection box to world start coordinates have been initialized
	UPROPERTY()
	bool bIsSelectBoxToWorldInit;

	// New location for the battle units to move to
	UPROPERTY()
	FVector NewDispatchDestination;
};

