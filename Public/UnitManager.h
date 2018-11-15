// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SelectionBox.h"
#include "UnitManager.generated.h"

UCLASS()
class STRATEGYAFTERNOON_API AUnitManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties.
	AUnitManager();

	// Called when the game starts or when spawned.
	virtual void BeginPlay() override;

	// Spawn new battle unit on the battlefield at the selected spawn location.
	void SpawnUnit(TSubclassOf<class ABattleUnitBase> UnitType, FVector const& SpawnLocation);

	// Destroys a battle unit and removes it from the array of active units.
	void DestroyUnit(class ABattleUnitBase* BattleUnit);

	// Adds to the array of selected units
	void AddToSelectedUnits(class ABattleUnitBase* Unit);

	// Clears the array of selected units.
	void ClearSelection();

	void SwapSelection(TArray<class ABattleUnitBase*> & NewSelection); 

	TArray<class ABattleUnitBase*> const& GetBattleUnits() const;

	TArray<class ABattleUnitBase*> const& GetSelectedUnits() const;

private:
	// Array which holds a reference to all spawned units in the level. 
	UPROPERTY()
	TArray<class ABattleUnitBase*> BattleUnits; 

	// Array which holds only the selected units. This array should not be used to modify object state.
	UPROPERTY()
	TArray<class ABattleUnitBase*> SelectedUnits; 

};
