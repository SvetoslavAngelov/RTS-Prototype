// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitMovementComponent.h"

void UUnitMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (UpdatedComponent)
	{
		FVector MovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.f) * DeltaTime * 100.f;
		FHitResult HitResult;
		SafeMoveUpdatedComponent(MovementThisFrame, UpdatedComponent->GetComponentRotation(), true, HitResult);
	}
}