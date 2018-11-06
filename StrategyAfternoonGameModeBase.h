// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StrategyAfternoonGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class STRATEGYAFTERNOON_API AStrategyAfternoonGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public: 
	virtual void BeginPlay() override; 

	UFUNCTION(BlueprintCallable, Category = "UnitSpawn")
	void SpawnBattleUnit(UPARAM() TSubclassOf<class ABattleUnitBase> UnitType, FVector const& SpawnLocation);

	UPROPERTY(BlueprintReadOnly, Category = "UnitManager")
	class AUnitManager* UnitManager; 
};
