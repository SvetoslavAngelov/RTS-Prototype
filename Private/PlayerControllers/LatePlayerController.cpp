// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/PlayerControllers/LatePlayerController.h"
#include "Public/Pawns/CameraPawn.h"
#include "Public/GameplayManagers/UnitManager.h"
#include "Public/Units/UnitBase.h"
#include "LateGameModeBase.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"


ALatePlayerController::ALatePlayerController()
{
	// Shows mouse cursor and enables click events
	bEnableClickEvents = true;
	bIsLMBPressed = false;
	bIsRMBPressed = false;

	MousePosition = { 0.f, 0.f };
	ViewportSize = { 0.f, 0.f };

	// Set default settings for AI move request 
	Destination = FAIMoveRequest(); 
	Destination.SetUsePathfinding(true);
	Destination.SetAllowPartialPath(true);
	Destination.SetProjectGoalLocation(true);
	Destination.SetReachTestIncludesAgentRadius(false);
	Destination.SetReachTestIncludesGoalRadius(false);
	Destination.SetCanStrafe(false);
	Destination.SetAcceptanceRadius(1.f);
}

void ALatePlayerController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;

	CameraPawn = Cast<ACameraPawn>(GetPawn());
	if (CameraPawn)
	{
		InitializeViewport(); 
		InitializeActiveViewport();
	}

	ALateGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ALateGameModeBase>();
	if (GameMode->UnitManager)
	{
		UnitManager = GameMode->UnitManager;
	}
}

void ALatePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetMousePosition(MousePosition.X, MousePosition.Y))
	{
		UpdateCamera();
		HighlightSingleUnit();
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
		AUnitBase* Unit = Cast<AUnitBase>(HitResult.GetActor());
		if (Unit && Destination.UpdateGoalLocation(Unit->GetActorLocation()))
		{
			Destination.SetGoalActor(Unit);
		}
		else if (Destination.UpdateGoalLocation(HitResult.ImpactPoint))
		{
			Destination.SetGoalLocation(HitResult.ImpactPoint);
		}
	}
	MoveSelectedUnits();
	bIsRMBPressed = true;
}

void ALatePlayerController::OnRMBReleased()
{
	bIsRMBPressed = false;
}


void ALatePlayerController::UpdateCamera() const
{
	if (CameraPawn)
	{
		CameraPawn->SetMouseScrollDirection(MousePosition.X, MousePosition.Y);
		CameraPawn->UpdateCameraPosition();
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
		FVector2D UnitLocation;
		if (ProjectWorldLocationToScreen(Unit->GetActorLocation(), UnitLocation))
		{
			float UnitCapsuleSize = Unit->GetUnitCapsuleSize();
			FBox2D UnitBoundingBox{ UnitLocation - UnitCapsuleSize, UnitLocation + UnitCapsuleSize };
			if (SelectionBox.Absolute().Intersect(UnitBoundingBox))
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
		AUnitBase* Unit = Cast<AUnitBase>(HitResult.GetActor());
		if (Unit)
		{
			UnitManager->ClearSelection();
			UnitManager->AddToSelectedUnits(Unit);
		}
	}
}

void ALatePlayerController::HighlightMultipleUnits() const
{
	for (auto Unit : UnitManager->GetUnits())
	{
		FVector2D UnitLocation;
		if (ProjectWorldLocationToScreen(Unit->GetActorLocation(), UnitLocation))
		{
			float UnitCapsuleSize = Unit->GetUnitCapsuleSize();
			FBox2D UnitBoundingBox{ UnitLocation - UnitCapsuleSize, UnitLocation + UnitCapsuleSize };
			if (SelectionBox.Absolute().Intersect(UnitBoundingBox))
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
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType; 
	FHitResult HitResult; 
	if (GetHitResultUnderCursorForObjects(ObjectType, false, HitResult))
	{
		AUnitBase* Unit = Cast<AUnitBase>(HitResult.GetActor());
		if (Unit)
		{
			Unit->bIsHighlighted = true;
			UnitManager->HighlightedUnit = Unit; 
		}
		else if (UnitManager->HighlightedUnit)
		{
			UnitManager->HighlightedUnit->bIsHighlighted = false;
			UnitManager->HighlightedUnit = nullptr; 
		}
	}
}

void ALatePlayerController::MoveSelectedUnits() const
{
	for (auto Unit : UnitManager->GetSelectedUnits())
	{
		// Calls the AI controller of each unit to execute the command
		Unit->MoveToDestination(Destination);
	}
}

void ALatePlayerController::InitializeViewport()
{
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
	}
}

void ALatePlayerController::InitializeActiveViewport()
{
	CameraPawn->InitializeActiveViewport(ViewportSize, 0.f);
}