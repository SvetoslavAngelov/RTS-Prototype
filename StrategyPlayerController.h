// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "StrategyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class STRATEGYAFTERNOON_API AStrategyPlayerController : public APlayerController
{
	GENERATED_BODY()

public: 
	// Default constructor
	AStrategyPlayerController(); 
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; 

	// Called every frame 
	virtual void Tick(float DeltaTime) override; 

	// Set up player input 
	virtual void SetupInputComponent() override; 

	// Mouse select interface
	void OnMousePressed(); 
	void OnMouseReleased();

	// Camera movement interface 
	void MoveCamera(FVector2D const& MousePosition, FIntPoint const& ViewportSize) const;

private: 
	UPROPERTY()
	class ACameraPawn* CameraPawn; 

	UPROPERTY()
	bool bIsSelected;
};
