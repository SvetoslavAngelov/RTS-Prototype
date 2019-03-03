// Fill out your copyright notice in the Description page of Project Settings.

#include "StructureUnit.h"

void AStructureUnit::BeginPlay()
{
	AUnitBase::BeginPlay();
}

void AStructureUnit::MoveToDestination(FAIMoveRequest const& Destination)
{
	UE_LOG(LogTemp, Warning, TEXT("Not moving!"));
}