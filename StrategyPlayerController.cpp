// Fill out your copyright notice in the Description page of Project Settings.

#include "StrategyPlayerController.h"
#include "CameraPawn.h"
#include "Public/UnitManager.h"
#include "StrategyAfternoonGameModeBase.h"
#include "Engine/World.h"


AStrategyPlayerController::AStrategyPlayerController()
{
	// Shows mouse cursor and enables click events
	bEnableClickEvents = true;
	bIsLMBPressed = false;
	bIsRMBPressed = false;
	bIsSelectBoxInit = false;
	bIsSelectBoxToWorldInit = false;

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
		// TODO Track mouse world position
		MoveCamera();
		if (bIsLMBPressed)
		{
			DefineSelectionBox();
			DefineSelectionBoxToWorld();
			// TODO Disselect previous units
			// TODO Select new units 
		}
		if (bIsRMBPressed)
		{
			// TODO Dispatch units 
		}
		SelectionBoxReset();
	}
}

void AStrategyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent(); 

	InputComponent->BindAction("Select", IE_Pressed, this, &AStrategyPlayerController::OnLMBPressed);
	InputComponent->BindAction("Select", IE_Released, this, &AStrategyPlayerController::OnLMBReleased);

	InputComponent->BindAction("Dispatch", IE_Pressed, this, &AStrategyPlayerController::OnRMBPressed);
	InputComponent->BindAction("Dispatch", IE_Released, this, &AStrategyPlayerController::OnRMBReleased);
}

void AStrategyPlayerController::OnLMBPressed()
{
	bIsLMBPressed = true;
}

void AStrategyPlayerController::OnLMBReleased()
{
	bIsLMBPressed = false;
}

void AStrategyPlayerController::OnRMBPressed()
{
	FHitResult HitResult;
	if (GetHitResultAtScreenPosition(MousePosition, CurrentClickTraceChannel, true, HitResult))
	{
		NewDispatchDestination = HitResult.ImpactPoint;
	}
	bIsRMBPressed = true; 
}

void AStrategyPlayerController::OnRMBReleased()
{
	bIsRMBPressed = false; 
	NewDispatchDestination = { 0.f, 0.f, 0.f };
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
	if (!bIsSelectBoxInit)
	{
		SelectionBox.PointB = SelectionBox.PointA = MousePosition;
		bIsSelectBoxInit = true;
	}
		SelectionBox.PointB = MousePosition;
}

void AStrategyPlayerController::SelectionBoxReset()
{
	if (!bIsLMBPressed)
	{
		SelectionBox.Reset();
		bIsSelectBoxInit = false;
		bIsSelectBoxToWorldInit = false;
	}
}

void AStrategyPlayerController::DefineSelectionBoxToWorld()
{
	FHitResult HitResult;
	if (!bIsSelectBoxToWorldInit)
	{
		GetHitResultAtScreenPosition(SelectionBox.PointA, CurrentClickTraceChannel, false, HitResult);
		SelectionBoxToWorld.PointB = SelectionBoxToWorld.PointA = { HitResult.ImpactPoint.X, HitResult.ImpactPoint.Y };
	}
	GetHitResultAtScreenPosition(SelectionBox.PointB, CurrentClickTraceChannel, false, HitResult);
	SelectionBoxToWorld.PointB = { HitResult.ImpactPoint.X, HitResult.ImpactPoint.Y };
}