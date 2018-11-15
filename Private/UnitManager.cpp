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

void AUnitManager::SpawnUnit(TSubclassOf<class ABattleUnitBase> UnitType, FVector const& SpawnLocation)
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
		if (SelectedUnits.Find(BattleUnit))
		{
			SelectedUnits.Pop(BattleUnit);
		}
		BattleUnits.Pop(BattleUnit);
		BattleUnit->Destroy();
	}
}

void AUnitManager::AddToSelectedUnits(class ABattleUnitBase* Unit)
{
	Unit->bIsActive = true;
	SelectedUnits.Add(Unit);
}

void AUnitManager::ClearSelection()
{	
	for (auto Unit : SelectedUnits)
	{
		Unit->bIsActive = false;
	}
	SelectedUnits.Empty();
}

TArray<class ABattleUnitBase*> const& AUnitManager::GetBattleUnits() const
{
	return BattleUnits; 
}

TArray<class ABattleUnitBase*> const& AUnitManager::GetSelectedUnits() const
{
	return SelectedUnits; 
}

void AUnitManager::SwapSelection(TArray<class ABattleUnitBase*> & NewSelection)
{
	if (NewSelection.Num() != 0)
	{
		ClearSelection();
		for (auto Unit : NewSelection)
		{
			AddToSelectedUnits(Unit);
		}
	}
}