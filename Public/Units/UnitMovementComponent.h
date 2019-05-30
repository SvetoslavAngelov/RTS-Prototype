// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Runtime/AIModule/Classes/AITypes.h"
#include "UnitMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class LATE_API UUnitMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
	UUnitMovementComponent(FObjectInitializer const& ObjectInitializer);

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void RequestMove(FAIMoveRequest const& Destination, TArray<FVector> const& UnitPath);

	void UpdatePath(TArray<FVector> const& NewPath);

	void UpdateOrientation(FRotator const& NewOrientation); 

	UPROPERTY(EditAnywhere, Category = "MoveSpeed")
	float MoveSpeed; 

	UPROPERTY()
	FRotator Orientation;

	UPROPERTY()
	TArray<FVector> Path; 

	UPROPERTY()
	FVector LastLocation;

	UPROPERTY()
	bool IsPathUpdated;
};

