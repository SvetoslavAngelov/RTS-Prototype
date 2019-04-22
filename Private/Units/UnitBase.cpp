// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Units/UnitBase.h"
#include "Public/Units/UnitMovementComponent.h"
#include "Public/AIControllers/UnitController.h"
#include "Public/GameplayManagers/CombatManager.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"

AUnitBase::AUnitBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// TODO For debug only
	bIsSpawned = false;
	bIsActive = false;
	bIsHighlighted = false;

	// Set up root component
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComponent; 

	// Set up collision box and root component
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->InitBoxExtent(FVector{ 45.f });

	// Set up skeletal mesh component
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	MeshComponent->SetupAttachment(RootComponent);

	// Set up characeter movement component
	MovementComponent = CreateDefaultSubobject<UUnitMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->bConstrainToPlane = true;
	MovementComponent->bSnapToPlaneAtStart = true;

	// Disables controller rotation.This removes conflict between movement controller and pawn rotation when new direction is set.
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
		UE_LOG(LogTemp, Warning, TEXT("UnitController %s"), *UnitController->GetName());
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
	UCombatManager::AttackUnit(Unit);
	// Move to unit locaiton
	// Notify UnitManager that a unit is being attacked 
}

float AUnitBase::GetUnitCapsuleSize() const
{
	// TODO
	return  45.f;
}

FVector AUnitBase::GetCollisionExtent() const
{
	return CollisionBox->GetScaledBoxExtent();
}


