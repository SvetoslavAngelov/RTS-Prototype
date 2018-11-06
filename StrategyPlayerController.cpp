// Fill out your copyright notice in the Description page of Project Settings.

#include "StrategyPlayerController.h"
#include "CameraPawn.h"
#include "Public/UnitManager.h"
#include "Public/Units/BattleUnitBase.h"
#include "StrategyAfternoonGameModeBase.h"
#include "Engine/World.h"


AStrategyPlayerController::AStrategyPlayerController()
{
	// Shows mouse cursor and enables click events
	bEnableClickEvents = true;
	bIsLMBPressed = false;
	bIsRMBPressed = false;

	MousePosition = { 0.f, 0.f };
	ViewportSize = { 0, 0 };

	NewDispatchDestination = { 0.f, 0.f, 0.f };
	
}

void AStrategyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	CameraPawn = Cast<ACameraPawn>(GetPawn());

	// TODO Consider replacing with GetGameMode()
	AStrategyAfternoonGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AStrategyAfternoonGameModeBase>();
	if (GameMode->UnitManager)
	{
		UnitManager = GameMode->UnitManager;
	}

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
			if (SelectionBox.isDragging())
			{
				SelectMultipleUnits();
			}
			else
			{
				SelectSingleUnit();
			}
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
	if (!SelectionBox.bIsInitialized)
	{
		SelectionBox.PointB = SelectionBox.PointA = MousePosition;
		SelectionBox.bIsInitialized = true;
	}
		SelectionBox.PointB = MousePosition;
}

void AStrategyPlayerController::SelectionBoxReset()
{
	if (!bIsLMBPressed)
	{
		SelectionBox.Reset();
	}
}

void AStrategyPlayerController::SelectMultipleUnits()
{
	for (auto Unit : UnitManager->BattleUnits)
	{
		FVector2D ScreenLocation;
		if (ProjectWorldLocationToScreen(Unit->GetActorLocation(), ScreenLocation))
		{
			if (SelectionBox.Absolute().IsInside(ScreenLocation))
			{
				Unit->bIsActive = true;
			}
		}
	}
}

void AStrategyPlayerController::SelectSingleUnit()
{
	FHitResult HitResult;
	if (GetHitResultAtScreenPosition(MousePosition, CurrentClickTraceChannel, false, HitResult))
	{
		ABattleUnitBase* Unit = Cast<ABattleUnitBase>(HitResult.Actor);
		if (Unit)
		{
			Unit->bIsActive = true; 
		}
	}
}