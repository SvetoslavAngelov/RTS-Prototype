// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitManager.h"
#include "Engine/World.h"
#include "BattleUnitBase.h"

// Sets default values
AUnitManager::AUnitManager()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AUnitManager::BeginPlay()
{
	Super::BeginPlay();

}

void AUnitManager::SpawnUnit(UPARAM() TSubclassOf<class ABattleUnitBase> UnitType, FVector const& SpawnLocation)
{
	FActorSpawnParameters SpawnParameters;
	FTransform TransformData;
	TransformData.SetLocation(SpawnLocation);
	BattleUnits.Add(GetWorld()->SpawnActor<ABattleUnitBase>(UnitType, TransformData, SpawnParameters));
}

void AUnitManager::DestroyUnit(ABattleUnitBase* BattleUnit)
{
	if (BattleUnit)
	{
		BattleUnits.Pop(BattleUnit);
		BattleUnit->Destroy();
	}
}

void AUnitManager::Debug()
{
	UE_LOG(LogTemp, Warning, TEXT("Alive!"));
}