// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/GameplayManagers/UnitManager.h"
#include "Public/Units/UnitBase.h"
#include "Engine/World.h"


// Sets default values
AUnitManager::AUnitManager()
{
	PrimaryActorTick.bCanEverTick = false;

	// No highlighted units at start of game 
	HighlightedUnit = nullptr;
}

void AUnitManager::BeginPlay()
{
	Super::BeginPlay();

}

void AUnitManager::SpawnUnit(TSubclassOf<AUnitBase> UnitType, FVector const& SpawnLocation)
{
	FActorSpawnParameters SpawnParameters;
	FTransform TransformData;
	TransformData.SetLocation(SpawnLocation);
	Units.Add(GetWorld()->SpawnActor<AUnitBase>(UnitType, TransformData, SpawnParameters));
}

void AUnitManager::DestroyUnit(AUnitBase* Unit)
{
	if (Unit)
	{
		if (SelectedUnits.Find(Unit))
		{
			SelectedUnits.Pop(Unit);
		}
		Units.Pop(Unit);
		Unit->Destroy();
	}
}

void AUnitManager::AddToSelectedUnits(AUnitBase* Unit)
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

TArray<class AUnitBase*> const& AUnitManager::GetUnits() const
{
	return Units;
}

TArray<class AUnitBase*> const& AUnitManager::GetSelectedUnits() const
{
	return SelectedUnits;
}

void AUnitManager::SwapSelection(TArray<class AUnitBase*> & NewSelection)
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
