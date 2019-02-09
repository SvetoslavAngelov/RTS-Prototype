// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnitManager.generated.h"

UCLASS()
class LATE_API AUnitManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties.
	AUnitManager();

	// Called when the game starts or when spawned.
	virtual void BeginPlay() override;

	// Spawn new battle unit on the battlefield at the selected spawn location.
	void SpawnUnit(TSubclassOf<class AUnitBase> UnitType, FVector const& SpawnLocation);

	// Destroys a battle unit and removes it from the array of active units.
	void DestroyUnit(class AUnitBase* BattleUnit);

	// Adds to the array of selected units
	void AddToSelectedUnits(class AUnitBase* Unit);

	// Clears the array of selected units.
	void ClearSelection();

	// Reassigns the unit indices in the array after a removal, starting from a set index in the array
	void UpdateUnitIndices(int32 const Index);

	void SwapSelection(TArray<class AUnitBase*> & NewSelection);

	TArray<class AUnitBase*> const& GetUnits() const;

	TArray<class AUnitBase*> const& GetSelectedUnits() const;

	UPROPERTY()
	class AUnitBase* HighlightedUnit;

private:
	// Array which holds a reference to all spawned units in the level. 
	UPROPERTY()
	TArray<class AUnitBase*> Units;

	// Array which holds only the selected units. This array should not be used to modify object state.
	UPROPERTY()
	TArray<class AUnitBase*> SelectedUnits;

};
