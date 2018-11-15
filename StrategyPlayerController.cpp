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
		}
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
	if (SelectionBox.isDragging())
	{
		SelectMultipleUnits();
	}
	else if (!SelectionBox.isDragging())
	{
		SelectSingleUnit();
	}
	SelectionBox.Reset();
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
	MoveSelectedUnitsTo(NewDispatchDestination);
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

void AStrategyPlayerController::SelectMultipleUnits() const
{
	TArray<ABattleUnitBase*> Temp; 

	for (auto Unit : UnitManager->GetBattleUnits())
	{
		FVector2D ScreenLocation;
		if (ProjectWorldLocationToScreen(Unit->GetActorLocation(), ScreenLocation))
		{	
			if (SelectionBox.Absolute().IsInside(ScreenLocation))
			{
				Temp.Add(Unit);
			}
		}	
	}
	UnitManager->SwapSelection(Temp);
}

void AStrategyPlayerController::SelectSingleUnit() const
{
	FHitResult HitResult;
	if (GetHitResultAtScreenPosition(MousePosition, CurrentClickTraceChannel, false, HitResult))
	{
		ABattleUnitBase* Unit = Cast<ABattleUnitBase>(HitResult.Actor);
		if (Unit)
		{
			UnitManager->ClearSelection();
			UnitManager->AddToSelectedUnits(Unit);
		}
	}
}

void AStrategyPlayerController::MoveSelectedUnitsTo(FVector const& NewDestination) const
{
	for (auto Unit : UnitManager->GetSelectedUnits())
	{
		Unit->MoveTo(NewDestination);
	}
}
