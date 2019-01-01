// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Public/Data/SelectionBox.h"
#include "Runtime/AIModule/Classes/AITypes.h"
#include "LatePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LATE_API ALatePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Default constructor
	ALatePlayerController();

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

	// Camera movement interface 
	void UpdateCamera() const;

	// Uses the battle units' screen space location to determine if they are within the selection box
	void SelectMultipleUnits() const;

	// Raycasts and checks result under mouse cursor, if a unit was hit it is set to selected
	void SelectSingleUnit() const;

	// Checks if the unit is withing the selection box and flags it as highlighted 
	void HighlightMultipleUnits() const;

	// Checks if a unit is under the mouse cursor and flags it as highlighted 
	void HighlightSingleUnit() const;

	// Sends the selected pawn to a new location
	void MoveSelectedUnits() const;

	void InitializeViewport(); 

	void InitializeActiveViewport();

	// Contains the coordinates of the mouse drag selection box
	UPROPERTY()
	FSelectionBox SelectionBox;

private:
	// Pointer to the camera pawn 
	UPROPERTY()
	class ACameraPawn* CameraPawn;

	// Unit manager which handles spawning and destroying of battle units
	class AUnitManager* UnitManager;

	// Current view port size. 
	// NOTE: This is different from resolution
	UPROPERTY()
	FVector2D ViewportSize;

	// Holds the current mouse position
	UPROPERTY()
	FVector2D MousePosition;

	// Checks if left mouse button is pressed 
	UPROPERTY()
	bool bIsLMBPressed;

	// Checks if right mouse button is pressed
	UPROPERTY()
	bool bIsRMBPressed;

	// New move destination for the unit 
	UPROPERTY()
	FAIMoveRequest Destination; 
};
