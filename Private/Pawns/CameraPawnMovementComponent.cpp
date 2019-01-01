// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Pawns/CameraPawnMovementComponent.h"

UCameraPawnMovementComponent::UCameraPawnMovementComponent()
{
	CameraScrollSpeed = 0.f; 
}

void UCameraPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (UpdatedComponent)
	{
		FVector MovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.f) * DeltaTime * CameraScrollSpeed;
		FHitResult HitResult; 
		SafeMoveUpdatedComponent(MovementThisFrame, UpdatedComponent->GetComponentRotation(), true, HitResult);
	}
}

void UCameraPawnMovementComponent::SetCameraScrollSpeed(float Speed)
{
	CameraScrollSpeed = Speed;
}