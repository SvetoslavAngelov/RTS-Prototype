// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BattleUnitBase.generated.h"

UCLASS()
class STRATEGYAFTERNOON_API ABattleUnitBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABattleUnitBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Move pawn to destination
	void MoveTo(FVector const& Destination) const;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Checks if the unit is currently selected by the player controller
	UPROPERTY(BlueprintReadOnly)
	bool bIsActive;

	UPROPERTY(BlueprintReadOnly)
	bool bIsHighlighted;

	UPROPERTY()
	class AUnitController* UnitController;
};
