// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Runtime/AIModule/Classes/AITypes.h"
#include "Public/Data/UnitBaseAttributes.h"
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

	// Calls the unit AI controller to move it to the given destination
	virtual void MoveToDestination(FAIMoveRequest const& Destination);

	// Sends a notification to the unit manager that an attack on the given unit has began
	virtual void BeginAttack(AUnitBase* Unit);

	// Returns the unit capsule radius to screen size ratio
	virtual float GetUnitCapsuleSize() const;

	// Checks if unit is spawned on the map 
	UPROPERTY(BlueprintReadWrite)
	bool bIsSpawned;

	// True if the unit is currently selected by the player
	UPROPERTY(BlueprintReadOnly)
	bool bIsActive;

	// True if the unit is currently highlighted by the mouse cursor
	UPROPERTY(BlueprintReadOnly)
	bool bIsHighlighted;

	UPROPERTY()
	class AUnitController* UnitController;

	UPROPERTY()
	class AUnitManager* UnitManager;

	// The position of the unit in the UnitManager's unit array
	UPROPERTY()
	int32 Index; 

	// Contains all unit properties such as health, armour and others
	UPROPERTY(EditAnywhere, Category = "Unit Properties")
	FUnitBaseAttributes UnitProperties;
};
