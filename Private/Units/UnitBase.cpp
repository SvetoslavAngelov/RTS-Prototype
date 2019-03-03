// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Units/UnitBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Public/AIControllers/UnitController.h"
#include "Public/GameplayManagers/UnitManager.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"


AUnitBase::AUnitBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// TODO For debug only
	bIsSpawned = false;
	bIsActive = false;
	bIsHighlighted = false;

	// Set up character movement component. Movement component is inherited from parent class.
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = { 0.f, 200.f, 0.f };
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	GetCharacterMovement()->MaxAcceleration = 400.f;

	// Disables controller rotation. This removes conflict between controller and pawn rotation when new direction is set. 
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	AutoPossessAI = EAutoPossessAI::Spawned;
	Index = -1;
}

void AUnitBase::BeginPlay()
{
	Super::BeginPlay();

	UnitController = Cast<AUnitController>(GetController());
	if (UnitController)
	{
		bIsSpawned = true;
	}
}

void AUnitBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUnitBase::MoveToDestination(FAIMoveRequest const& Destination)
{
	if (UnitController)
	{
		UnitController->MoveTo(Destination);
	}
}

void AUnitBase::BeginAttack(AUnitBase* Unit)
{
	// Move to unit locaiton
	// Notify UnitManager that a unit is being attacked 
	
}

float AUnitBase::GetUnitCapsuleSize() const
{
	return  GetCapsuleComponent()->GetScaledCapsuleRadius();
}


