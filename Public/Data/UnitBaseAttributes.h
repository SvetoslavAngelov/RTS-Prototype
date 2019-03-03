// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnitBaseAttributes.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FUnitBaseAttributes 
{
	GENERATED_USTRUCT_BODY()

	// Default constructor
	FUnitBaseAttributes();

	UPROPERTY(EditAnywhere)
	float Health; 

	UPROPERTY(EditAnywhere)
	float Armour; 

	UPROPERTY(EditAnywhere)
	float Damage;
};