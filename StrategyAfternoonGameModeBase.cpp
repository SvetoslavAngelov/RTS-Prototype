// Fill out your copyright notice in the Description page of Project Settings.

#include "StrategyAfternoonGameModeBase.h"
#include "Public/UnitManager.h"
#include "Engine/World.h"

void AStrategyAfternoonGameModeBase::BeginPlay()
{
	Super::BeginPlay(); 
	UnitManager = GetWorld()->SpawnActor<AUnitManager>();
}

void AStrategyAfternoonGameModeBase::SpawnBattleUnit(UPARAM() TSubclassOf<class ABattleUnitBase> UnitType, FVector const& SpawnLocation)
{
	if(UnitManager)
		UnitManager->SpawnUnit(UnitType, SpawnLocation);
}