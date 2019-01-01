// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/UnitBase.h"
#include "Runtime/AIModule/Classes/AITypes.h"
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
	virtual void MoveToDestination(FAIMoveRequest const& Destination) const override; 
};
