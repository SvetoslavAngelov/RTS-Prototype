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
	// Set default spawn paramanters including spawn location
	FActorSpawnParameters SpawnParameters;
	FTransform TransformData;
	TransformData.SetLocation(SpawnLocation);

	// Spawn new unit
	AUnitBase* Unit = GetWorld()->SpawnActor<AUnitBase>(UnitType, TransformData, SpawnParameters);

	// Set the unit's location in the unit array
	if (Unit)
	{
		Unit->Index = Units.Add(Unit);
	}
}

void AUnitManager::DestroyUnit(AUnitBase* Unit)
{
	if (Unit)
	{
		// First search for unit in selected units array and remove if found
		int32 Index = SelectedUnits.Find(Unit);
		if (Index != INDEX_NONE)
		{
			SelectedUnits.RemoveAt(Index);
		}

		// Remove from units array
		Units.RemoveAt(Unit->Index);

		// Re-arrange unit indices in unit array
		UpdateUnitIndices(Unit->Index);

		// Remove from play and deallocate memory
		Unit->Destroy();
	}
}

void AUnitManager::UpdateUnitIndices(int32 const Index)
{
	for (int32 i{ Index }; i < Units.Num(); ++i)
	{
		Units[i]->Index = i;
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
