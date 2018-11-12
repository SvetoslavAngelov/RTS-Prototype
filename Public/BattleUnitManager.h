// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "BattleUnitManager.generated.h"

/**
 * 
 */
UCLASS()
class STRATEGYAFTERNOON_API ABattleUnitManager : public ASpectatorPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABattleUnitManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Spawn new battle unit on the battlefield at the selected spawn location
	UFUNCTION(BlueprintCallable, Category = "ObjectType")
	void SpawnUnit(UPARAM() TSubclassOf<class ABattleUnitBase> UnitType, FVector const& SpawnLocation);

	// Destroys a battle unit and removes it from the array of active units
	void DestroyUnit(class ABattleUnitBase* BattleUnit);

	void Debug();

private:
	UPROPERTY()
	TArray<class ABattleUnitBase*> BattleUnits;
};