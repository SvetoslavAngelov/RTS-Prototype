// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "CameraPawnMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class LATE_API UCameraPawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
	UCameraPawnMovementComponent();
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetCameraScrollSpeed(float Speed);

private:
	UPROPERTY()
	float CameraScrollSpeed;
};
