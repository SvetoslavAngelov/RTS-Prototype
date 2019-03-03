// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/UnitBase.h"
#include "StructureUnit.generated.h"

/**
 * 
 */
UCLASS()
class LATE_API AStructureUnit : public AUnitBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	// Calls the unit AI controller to move it to the given destination
	virtual void MoveToDestination(FAIMoveRequest const& Destination) override;

};
