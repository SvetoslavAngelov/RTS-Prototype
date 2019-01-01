// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackUnit.h"

void AAttackUnit::BeginPlay()
{
	AUnitBase::BeginPlay();
}

void AAttackUnit::MoveToDestination(FAIMoveRequest const& Destination) const
{
	AUnitBase::MoveToDestination(Destination);
}