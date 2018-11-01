// Fill out your copyright notice in the Description page of Project Settings.

#include "SelectionBox.h"

FSelectionBox::FSelectionBox()
	: PointA{ 0.f, 0.f }, PointB{ 0.f, 0.f } {}

void FSelectionBox::Reset()
{
	PointA = PointB = { 0.f, 0.f };
}
