// Fill out your copyright notice in the Description page of Project Settings.

#include "StrategyPlayerController.h"
#include "CameraPawn.h"
#include "Public/Units/BattleUnitBase.h"
#include "Public/UnitManager.h"


AStrategyPlayerController::AStrategyPlayerController()
{
	// Shows mouse cursor and enables click events
	bEnableClickEvents = true;
	bIsSelected = false;
	bIsVariableInitialized = false;

	MousePosition = { 0.f, 0.f };
	ViewportSize = { 0, 0 };

	NewDispatchDestination = { 0.f, 0.f, 0.f };

}

void AStrategyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	CameraPawn = Cast<ACameraPawn>(GetPawn());

	// TODO Works only in editor window not in standalone game
	GetViewportSize(ViewportSize.X, ViewportSize.Y);
}

void AStrategyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (GetMousePosition(MousePosition.X, MousePosition.Y))
	{
		DefineSelectionBox();
		MoveCamera();
	}
	
	if (bIsSelected)
	{
		FHitResult HitResult; 
		GetHitResultAtScreenPosition(MousePosition, CurrentClickTraceChannel , true, HitResult);

		UE_LOG(LogTemp, Warning, TEXT("Mouse selected! %s"), *HitResult.GetActor()->GetName());
	}


}

void AStrategyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent(); 

	InputComponent->BindAction("Select", IE_Pressed, this, &AStrategyPlayerController::OnMousePressed);
	InputComponent->BindAction("Select", IE_Released, this, &AStrategyPlayerController::OnMouseReleased);

	InputComponent->BindAction("Dispatch", IE_Pressed, this, &AStrategyPlayerController::SetUnitDispatchLocation);
}

void AStrategyPlayerController::OnMousePressed()
{
	bIsSelected = true;
}

void AStrategyPlayerController::OnMouseReleased()
{
	bIsSelected = false; 
}

void AStrategyPlayerController::MoveCamera() const
{
	if (CameraPawn)
	{
		if (FMath::TruncToInt(MousePosition.X) == 0)
		{
			CameraPawn->MoveLeft();
		}
		if (FMath::TruncToInt(MousePosition.X) == ViewportSize.X - 1) // TODO The tip of the mouse pointer takes one pixel, if 0 it won't register the screen border. 
		{
			CameraPawn->MoveRight();
		}
		if (FMath::TruncToInt(MousePosition.Y) == 0)
		{
			CameraPawn->MoveForward();
		}
		if (FMath::TruncToInt(MousePosition.Y) == ViewportSize.Y - 1) // TODO The tip of the mouse pointer takes one pixel, if 0 it won't register the screen border. 
		{
			CameraPawn->MoveBackward();
		}
	}
}

void AStrategyPlayerController::DefineSelectionBox()
{
	if (bIsSelected && !bIsVariableInitialized)
	{
		SelectionBox.PointB = SelectionBox.PointA = MousePosition;
		bIsVariableInitialized = true;
	}
	else if (bIsSelected && bIsVariableInitialized)
	{
		SelectionBox.PointB = MousePosition;
	} 
	else if (!bIsSelected)
	{
		SelectionBox.Reset();
		bIsVariableInitialized = false;
	}
}


void AStrategyPlayerController::SetUnitDispatchLocation()
{
	FHitResult HitResult; 
	if (GetHitResultAtScreenPosition(MousePosition, CurrentClickTraceChannel, true, HitResult))
	{
		// Set a new location for the units to move to
		// TODO add a check for minimum distance to allow proper animation display (when animations are implemented)
		NewDispatchDestination = HitResult.ImpactPoint;
	}
}