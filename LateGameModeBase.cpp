// Fill out your copyright notice in the Description page of Project Settings.

#include "LateGameModeBase.h"
#include "Public/GameplayManagers/UnitManager.h"
#include "Engine/World.h"

void ALateGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	UnitManager = GetWorld()->SpawnActor<AUnitManager>();
}

void ALateGameModeBase::SpawnUnit(UPARAM() TSubclassOf<class AUnitBase> UnitType, FVector const& SpawnLocation)
{
	if (UnitManager)
	{
		UnitManager->SpawnUnit(UnitType, SpawnLocation);
	}
}

void ALateGameModeBase::DestroyUnit()
{
	UnitManager->DestroyUnit(UnitManager->GetUnits()[0]); // TODO DEBUG!!!
}