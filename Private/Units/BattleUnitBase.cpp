// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Units/BattleUnitBase.h"
#include "StrategyPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Public/UnitController.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABattleUnitBase::ABattleUnitBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// TODO For debug only
	bIsActive = false;
	bIsHighlighted = false; 

	// Set up character movement component. Movement component is inherited from parent class.
	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = { 0.f, 200.f, 0.f };
	GetCharacterMovement()->bConstrainToPlane = true; 
	GetCharacterMovement()->bSnapToPlaneAtStart = true; 

	// Disables controller rotation. This removes conflict between controller and pawn rotation when new direction is set. 
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false; 
	bUseControllerRotationRoll = false;

	AutoPossessAI = EAutoPossessAI::Spawned;
}

// Called when the game starts or when spawned
void ABattleUnitBase::BeginPlay()
{
	Super::BeginPlay();

	UnitController = Cast<AUnitController>(GetController());
}

// Called every frame
void ABattleUnitBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABattleUnitBase::MoveTo(FVector const& Destination) const
{
	if (UnitController)
	{
		UnitController->MoveToLocation(Destination, -1.f, true, true, false, false);
	}
}

