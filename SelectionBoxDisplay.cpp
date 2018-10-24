// Fill out your copyright notice in the Description page of Project Settings.

#include "SelectionBoxDisplay.h"
#include "StrategyPlayerController.h"

ASelectionBoxDisplay::ASelectionBoxDisplay()
{
	// Default colour of the selection box set to green
	OutlineColour = FColor::Green;

	// Default fill colour of the selection box set to pale green
	FillColour = { 0.f, 1.f, 0.f, 0.2f };

	// Default thickness of the selection box set to 1 pixel
	SelectionBoxThickness = 1.f;

	SelectionBox = nullptr;
}

void ASelectionBoxDisplay::BeginPlay()
{
	Super::BeginPlay();

	// Find active player controller and assign a pointer to its selection box
	AStrategyPlayerController* PlayerController = Cast<AStrategyPlayerController>(GetOwningPlayerController());
	if (PlayerController)
	{
		SelectionBox = &PlayerController->SelectionBox;
	}
}

void ASelectionBoxDisplay::DrawHUD()
{
	Super::DrawHUD();

	// TODO increase performance by removing the SelectionBox checks 
	DrawSelectionBox();
	FillSelectionBox();
}

void ASelectionBoxDisplay::DrawSelectionBox()
{
	if (SelectionBox)
	{
		// Draw side A
		DrawLine(SelectionBox->PointA.X, SelectionBox->PointA.Y, SelectionBox->PointB.X, SelectionBox->PointA.Y, OutlineColour, SelectionBoxThickness);

		// Draw side B
		DrawLine(SelectionBox->PointB.X, SelectionBox->PointA.Y, SelectionBox->PointB.X, SelectionBox->PointB.Y, OutlineColour, SelectionBoxThickness);

		// Draw side C
		DrawLine(SelectionBox->PointB.X, SelectionBox->PointB.Y, SelectionBox->PointA.X, SelectionBox->PointB.Y, OutlineColour, SelectionBoxThickness);

		// Draw side D
		DrawLine(SelectionBox->PointA.X, SelectionBox->PointB.Y, SelectionBox->PointA.X, SelectionBox->PointA.Y, OutlineColour, SelectionBoxThickness);
	}
}

void ASelectionBoxDisplay::FillSelectionBox()
{
	if(SelectionBox)
	{
		// Fill a rectangle with a set colour at given screen coordinates
		DrawRect(	FillColour, 
					SelectionBox->PointA.X, 
					SelectionBox->PointA.Y, 
					SelectionBox->PointB.X - SelectionBox->PointA.X, 
					SelectionBox->PointB.Y - SelectionBox->PointA.Y);
	}
}