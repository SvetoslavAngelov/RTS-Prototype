// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/HUD/SelectionBoxHUD.h"
#include "Public/PlayerControllers/LatePlayerController.h"

ASelectionBoxHUD::ASelectionBoxHUD()
{
	// Default colour of the selection box set to green
	OutlineColour = FColor::Green;

	// Default fill colour of the selection box set to pale green
	FillColour = { 0.f, 1.f, 0.f, 0.2f };

	// Default thickness of the selection box set to 1 pixel
	SelectionBoxThickness = 1.f;

	SelectionBox = nullptr;
}

void ASelectionBoxHUD::BeginPlay()
{
	Super::BeginPlay();

	// Find active player controller and assign a pointer to its selection box
	ALatePlayerController* PlayerController = Cast<ALatePlayerController>(GetOwningPlayerController());
	if (PlayerController)
	{
		SelectionBox = &PlayerController->SelectionBox;
	}
}

void ASelectionBoxHUD::DrawHUD()
{
	Super::DrawHUD();

	// TODO increase performance by removing the SelectionBox checks 
	DrawSelectionBox();
	FillSelectionBox();
}

void ASelectionBoxHUD::DrawSelectionBox()
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

void ASelectionBoxHUD::FillSelectionBox()
{
	if (SelectionBox)
	{
		// Fill a rectangle with a set colour at given screen coordinates
		DrawRect(FillColour,
			SelectionBox->PointA.X,
			SelectionBox->PointA.Y,
			SelectionBox->PointB.X - SelectionBox->PointA.X,
			SelectionBox->PointB.Y - SelectionBox->PointA.Y);
	}
}