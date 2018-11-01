// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitManager.h"
#include "Engine/World.h"
#include "BattleUnitBase.h"

// Sets default values
AUnitManager::AUnitManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUnitManager::BeginPlay()
{
	Super::BeginPlay();

}


void AUnitManager::DestroyUnit(class ABattleUnit* BattleUnit)
{

}

void AUnitManager::SpawnUnit(UPARAM() TSubclassOf<class ABattleUnitBase> UnitType, FVector const& SpawnLocation)
{
	FActorSpawnParameters SpawnParameters;
	FTransform TransformData;
	TransformData.SetLocation(SpawnLocation);
	BattleUnits.Add(GetWorld()->SpawnActor<ABattleUnitBase>(UnitType, TransformData, SpawnParameters));
}
