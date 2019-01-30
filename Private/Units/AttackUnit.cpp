// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackUnit.h"

AAttackUnit::AAttackUnit()
{
	bIsRunning = false;
	bIsSpawned = false;
}

void AAttackUnit::BeginPlay()
{
	AUnitBase::BeginPlay();

	if (UnitController)
	{
		bIsSpawned = true;
	}
}

void AAttackUnit::Tick(float DeltaTime)
{
	AUnitBase::Tick(DeltaTime);

	if (GetVelocity().X != 0)
	{
		bIsRunning = true;
	}
	else
	{
		bIsRunning = false;
	}
}

void AAttackUnit::MoveToDestination(FAIMoveRequest const& Destination) const
{
	AUnitBase::MoveToDestination(Destination);
}