// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LateGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class LATE_API ALateGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "UnitSpawn")
	void SpawnUnit(UPARAM() TSubclassOf<class AUnitBase> UnitType, FVector const& SpawnLocation);

	UFUNCTION(BlueprintCallable, Category = "DestroyUnit")
	void DestroyUnit();

	UPROPERTY(BlueprintReadOnly, Category = "UnitManager")
	class AUnitManager* UnitManager;
};
