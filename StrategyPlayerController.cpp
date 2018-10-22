// Fill out your copyright notice in the Description page of Project Settings.

#include "StrategyPlayerController.h"
#include "CameraPawn.h"


AStrategyPlayerController::AStrategyPlayerController()
{
	// Shows mouse cursor and enables click events
	bEnableClickEvents = true;
	bIsSelected = false;
}

void AStrategyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;

	CameraPawn = Cast<ACameraPawn>(GetPawn());

	if (CameraPawn)
	{
		Possess(CameraPawn);
		UE_LOG(LogTemp, Warning, TEXT("Camera pawn: %s "), *CameraPawn->GetName());
	}
}

void AStrategyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector2D MousePosition; 
	FIntPoint ViewportSize;
	
	GetViewportSize(ViewportSize.X, ViewportSize.Y);

	if (GetMousePosition(MousePosition.X, MousePosition.Y))
	{
		MoveCamera(MousePosition, ViewportSize);
	}
	   
	if (bIsSelected)
	{
		UE_LOG(LogTemp, Warning, TEXT("Mouse selected!"));
	}
}

void AStrategyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent(); 

	InputComponent->BindAction("Select", IE_Pressed, this, &AStrategyPlayerController::OnMousePressed);
	InputComponent->BindAction("Select", IE_Released, this, &AStrategyPlayerController::OnMouseReleased);
}

void AStrategyPlayerController::OnMousePressed()
{
	bIsSelected = true; 
}

void AStrategyPlayerController::OnMouseReleased()
{
	bIsSelected = false; 
}

void AStrategyPlayerController::MoveCamera(FVector2D const& MousePosition, FIntPoint const& ViewportSize) const
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
