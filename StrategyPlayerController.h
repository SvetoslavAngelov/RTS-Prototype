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

	// Sets the selection box dimensions back to defaults (0)
	void SelectionBoxReset();

	// Camera movement interface 
	void MoveCamera() const;

	// Uses the battle units' screen space location to determine if they are within the selection box
	void SelectMultipleUnits() const;

	// Raycasts and checks result under mouse cursor, if a unit was hit it is set to selected
	void SelectSingleUnit() const;

	void UnselectUnits() const; 

	// Sends the selected pawn to a new location
	void MoveSelectedUnitsTo(FVector const& NewDestination) const;

	// Contains the coordinates of the mouse drag selection box
	UPROPERTY()
	FSelectionBox SelectionBox;

private: 
	// Pointer to the camera pawn 
	UPROPERTY()
	class ACameraPawn const* CameraPawn; 

	// Unit manager which handles spawning and destroying of battle units
	class AUnitManager const* UnitManager;

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

	// New location for the battle units to move to
	UPROPERTY()
	FVector NewDispatchDestination;
};

