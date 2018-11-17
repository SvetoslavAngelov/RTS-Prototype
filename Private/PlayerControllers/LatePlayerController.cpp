// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/PlayerControllers/LatePlayerController.h"
#include "Public/Pawns/CameraPawn.h"
#include "Public/GameplayManagers/UnitManager.h"
#include "Public/Units/UnitBase.h"
#include "LateGameModeBase.h"
#include "Engine/World.h"


ALatePlayerController::ALatePlayerController()
{
	// Shows mouse cursor and enables click events
	bEnableClickEvents = true;
	bIsLMBPressed = false;
	bIsRMBPressed = false;

	MousePosition = { 0.f, 0.f };
	ViewportSize = { 0, 0 };

	NewDispatchDestination = { 0.f, 0.f, 0.f };
}

void ALatePlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	CameraPawn = Cast<ACameraPawn>(GetPawn());

	// TODO Consider replacing with GetGameMode()
	ALateGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ALateGameModeBase>();
	if (GameMode->UnitManager)
	{
		UnitManager = GameMode->UnitManager;
	}

	// TODO Works only in editor window not in standalone game
	GetViewportSize(ViewportSize.X, ViewportSize.Y);
}

void ALatePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetMousePosition(MousePosition.X, MousePosition.Y))
	{
		// TODO Track mouse world position
		MoveCamera();
		if (bIsLMBPressed)
		{
			DefineSelectionBox();
			HighlightMultipleUnits();
		}
	}
}

void ALatePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Select", IE_Pressed, this, &ALatePlayerController::OnLMBPressed);
	InputComponent->BindAction("Select", IE_Released, this, &ALatePlayerController::OnLMBReleased);

	InputComponent->BindAction("Dispatch", IE_Pressed, this, &ALatePlayerController::OnRMBPressed);
	InputComponent->BindAction("Dispatch", IE_Released, this, &ALatePlayerController::OnRMBReleased);
}

void ALatePlayerController::OnLMBPressed()
{
	bIsLMBPressed = true;
}

void ALatePlayerController::OnLMBReleased()
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

void ALatePlayerController::OnRMBPressed()
{
	FHitResult HitResult;
	if (GetHitResultAtScreenPosition(MousePosition, CurrentClickTraceChannel, true, HitResult))
	{
		NewDispatchDestination = HitResult.ImpactPoint;
	}
	bIsRMBPressed = true;
}

void ALatePlayerController::OnRMBReleased()
{
	bIsRMBPressed = false;
	MoveSelectedUnitsTo(NewDispatchDestination);
}


void ALatePlayerController::MoveCamera() const
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

void ALatePlayerController::DefineSelectionBox()
{
	if (!SelectionBox.bIsInitialized)
	{
		SelectionBox.PointB = SelectionBox.PointA = MousePosition;
		SelectionBox.bIsInitialized = true;
	}
	SelectionBox.PointB = MousePosition;
}

void ALatePlayerController::SelectMultipleUnits() const
{
	TArray<AUnitBase*> Temp;

	for (auto Unit : UnitManager->GetUnits())
	{
		Unit->bIsHighlighted = false;
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

void ALatePlayerController::SelectSingleUnit() const
{
	FHitResult HitResult;
	if (GetHitResultAtScreenPosition(MousePosition, CurrentClickTraceChannel, false, HitResult))
	{
		AUnitBase* Unit = Cast<AUnitBase>(HitResult.Actor);
		if (Unit)
		{
			UnitManager->ClearSelection();
			UnitManager->AddToSelectedUnits(Unit);
		}
	}
}

void ALatePlayerController::MoveSelectedUnitsTo(FVector const& NewDestination) const
{
	for (auto Unit : UnitManager->GetSelectedUnits())
	{
		Unit->MoveTo(NewDestination);
	}
}

void ALatePlayerController::HighlightMultipleUnits() const
{
	for (auto Unit : UnitManager->GetUnits())
	{
		FVector2D ScreenLocation;
		if (ProjectWorldLocationToScreen(Unit->GetActorLocation(), ScreenLocation))
		{
			if (SelectionBox.Absolute().IsInside(ScreenLocation))
			{
				Unit->bIsHighlighted = true;
			}
			else
			{
				Unit->bIsHighlighted = false;
			}
		}
	}
}

void ALatePlayerController::HighlightSingleUnit() const
{

}