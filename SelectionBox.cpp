// Fill out your copyright notice in the Description page of Project Settings.

#include "SelectionBox.h"

FSelectionBox::FSelectionBox()
	: PointA{ 0.f, 0.f }, PointB{ 0.f, 0.f } {}

FSelectionBox::FSelectionBox(float PointAX, float PointAY, float PointBX, float PointBY)
	: PointA{ PointAX, PointAY }, PointB{ PointBX, PointBY } {}

FSelectionBox::FSelectionBox(FVector2D const& PointA, FVector2D const& PointB)
	: PointA{ PointA }, PointB{ PointB }{}

void FSelectionBox::Reset()
{
	PointA = PointB = { 0.f, 0.f };
}
