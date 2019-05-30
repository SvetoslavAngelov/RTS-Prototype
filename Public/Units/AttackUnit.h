// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/UnitBase.h"
#include "AttackUnit.generated.h"

/**
 * 
 */
UCLASS()
class LATE_API AAttackUnit : public AUnitBase
{
	GENERATED_BODY()
	
public: 
	virtual void BeginPlay() override; 
	virtual void Tick(float DeltaTime) override;

	// Calls the unit AI controller to move it to the given destination
	virtual void MoveToDestination(FAIMoveRequest const& Destination) override;

	/*  ANIMATION INTERFACE  */

	// Checks if the unit is moving
	UPROPERTY(BlueprintReadWrite)
	bool bIsRunning;
};
