// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "CameraPawnMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class STRATEGYAFTERNOON_API UCameraPawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public: 
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override; 

	UPROPERTY(EditAnywhere, Category = "Camera pan speed")
	float CameraMoveSpeed = 450.f;
};
