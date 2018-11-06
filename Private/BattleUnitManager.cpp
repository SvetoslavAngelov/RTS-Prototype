// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleUnitManager.h"
#include "Engine/World.h"
#include "BattleUnitBase.h"

// Sets default values
ABattleUnitManager::ABattleUnitManager()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ABattleUnitManager::BeginPlay()
{
	Super::BeginPlay();

}

void ABattleUnitManager::SpawnUnit(UPARAM() TSubclassOf<class ABattleUnitBase> UnitType, FVector const& SpawnLocation)
{
	FActorSpawnParameters SpawnParameters;
	FTransform TransformData;
	TransformData.SetLocation(SpawnLocation);
	BattleUnits.Add(GetWorld()->SpawnActor<ABattleUnitBase>(UnitType, TransformData, SpawnParameters));
}

void ABattleUnitManager::DestroyUnit(ABattleUnitBase* BattleUnit)
{
	if (BattleUnit)
	{
		BattleUnits.Pop(BattleUnit);
		BattleUnit->Destroy();
	}
}

void ABattleUnitManager::Debug()
{
	UE_LOG(LogTemp, Warning, TEXT("Alive!"));
}