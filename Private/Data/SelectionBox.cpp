// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Data/SelectionBox.h"

FSelectionBox::FSelectionBox()
	: PointA{ 0.f, 0.f }, PointB{ 0.f, 0.f }, bIsInitialized{ false } {}

FSelectionBox::FSelectionBox(float PointAX, float PointAY, float PointBX, float PointBY)
	: PointA{ PointAX, PointAY }, PointB{ PointBX, PointBY }, bIsInitialized{ false } {}

FSelectionBox::FSelectionBox(FVector2D const& PointA, FVector2D const& PointB)
	: PointA{ PointA }, PointB{ PointB }, bIsInitialized{ false } {}

void FSelectionBox::Reset()
{
	PointA = PointB = { 0.f, 0.f };
	bIsInitialized = false;
}

FBox2D FSelectionBox::Absolute() const
{
	if (PointA.X < PointB.X && PointA.Y > PointB.Y)
		return { {PointA.X, PointB.Y}, {PointB.X, PointA.Y } };
	if (PointA.X > PointB.X && PointA.Y < PointB.Y)
		return { {PointB.X, PointA.Y}, {PointA.X, PointB.Y } };
	if (PointA.X > PointB.X && PointA.Y > PointB.Y)
		return { PointB, PointA };

	return { PointA, PointB };
}

bool FSelectionBox::isDragging() const
{
	if (PointA != PointB)
		return true;

	return false;
}
