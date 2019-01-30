// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Runtime/AIModule/Classes/AITypes.h"
#include "UnitBase.generated.h"

UCLASS()
class LATE_API AUnitBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUnitBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Move pawn to destination
	virtual void MoveToDestination(FAIMoveRequest const& Destination) const;

	// Returns the unit capsule radius to screen size ratio
	virtual float GetUnitCapsuleSize() const;

	// True if the unit is currently selected by the player
	UPROPERTY(BlueprintReadOnly)
	bool bIsActive;

	// True if the unit is currently highlighted by the mouse cursor
	UPROPERTY(BlueprintReadOnly)
	bool bIsHighlighted;

	UPROPERTY()
	class AUnitController* UnitController;

};
