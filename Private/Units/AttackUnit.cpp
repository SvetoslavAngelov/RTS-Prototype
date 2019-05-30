// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackUnit.h"
#include "Public/Units/UnitMovementComponent.h"

void AAttackUnit::BeginPlay()
{
	AUnitBase::BeginPlay();

	bIsRunning = false;
}

void AAttackUnit::Tick(float DeltaTime)
{
	AUnitBase::Tick(DeltaTime);

	/*if (GetVelocity().X != 0)
	{
		bIsRunning = true;
	}
	else
	{
		bIsRunning = false;
	}*/
}

void AAttackUnit::MoveToDestination(FAIMoveRequest const& Destination)
{
	AUnitBase::MoveToDestination(Destination);
}