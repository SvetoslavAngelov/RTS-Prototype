// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraPawnMovementComponent.h"

void UCameraPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Make sure that everything is still valid, and that we are allowed to move.
	if (PawnOwner || UpdatedComponent || !ShouldSkipUpdate(DeltaTime))
	{
		// Get (and then clear) the movement vector that we set in ACollidingPawn::Tick
		FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * CameraMoveSpeed;
		if (!DesiredMovementThisFrame.IsNearlyZero())
		{
			FHitResult Hit;
			SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);
		}
	}
}