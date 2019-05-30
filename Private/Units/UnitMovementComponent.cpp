// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitMovementComponent.h"

UUnitMovementComponent::UUnitMovementComponent(FObjectInitializer const& ObjectInitializer)
	: Super( ObjectInitializer )
{
	MoveSpeed = 400.f;
	Orientation = FRotator{ 0.f, 0.f, 0.f };
	LastLocation = FVector{ 0.f, 0.f, 0.f };
	IsPathUpdated = false;
}

void UUnitMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PawnOwner || UpdatedComponent || !ShouldSkipUpdate(DeltaTime))
	{
		if (IsPathUpdated)
		{
			Velocity = UpdatedComponent->GetForwardVector() * MoveSpeed * DeltaTime;
			MoveUpdatedComponent(Velocity, Orientation, true);
			UpdateComponentVelocity();
		}
	}
}

void UUnitMovementComponent::RequestMove(FAIMoveRequest const& Destination, TArray<FVector> const& UnitPath)
{
	
}