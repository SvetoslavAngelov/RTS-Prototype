// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatManager.generated.h"

/**
 * 
 */

UCLASS()
class UCombatManager : public UObject
{
	GENERATED_UCLASS_BODY()

public: 
	static void AttackUnit(class AUnitBase* Unit); 

};
