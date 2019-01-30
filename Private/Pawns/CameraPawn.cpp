// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Pawns/CameraPawn.h"
#include "Public/Pawns/CameraPawnMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ACameraPawn::ACameraPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Set up root component 
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.f);

	// Set up spring arm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 800.f;
	SpringArm->RelativeRotation = { -50.f, 0.f, 0.f };

	// Set up camera component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	// Set up movement component
	MovementComponent = CreateDefaultSubobject<UCameraPawnMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = RootComponent;

	// Set camera scroll speed
	CameraScrollSpeed = 450.f;
	MovementComponent->SetCameraScrollSpeed(CameraScrollSpeed);

	// Set mouse scroll direction at start of game
	MouseScrollDirection = EMouseScrollDirection::Centre;

	// Set default active viewport size 
	ActiveViewportSize = { 0.f,0.f };
}

void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();

}

void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UPawnMovementComponent* ACameraPawn::GetMovementComponent() const
{
	return MovementComponent;
}

void ACameraPawn::UpdateCameraPosition() const
{
	if (MovementComponent)
	{
		switch (MouseScrollDirection)
		{
			case(EMouseScrollDirection::Left)
				: MovementComponent->AddInputVector(GetActorRightVector() * -1.f);
				break; 
			case(EMouseScrollDirection::Right)
				: MovementComponent->AddInputVector(GetActorRightVector());
				break;
			case(EMouseScrollDirection::Top)
				: MovementComponent->AddInputVector(GetActorForwardVector());
				break;
			case(EMouseScrollDirection::Bottom)
				: MovementComponent->AddInputVector(GetActorForwardVector() * -1.f);
				break;
			default
				: break;
		}
	}
}

EMouseScrollDirection ACameraPawn::GetMouseScrollDirection() const
{
	return MouseScrollDirection; 
}

EMouseScrollDirection ACameraPawn::SetMouseScrollDirection(int32 MousePositionX, int32 MousePositionY)
{
	if (MousePositionX == 0)
		return MouseScrollDirection = EMouseScrollDirection::Left;
	else if (MousePositionX == ActiveViewportSize.X)
		return MouseScrollDirection = EMouseScrollDirection::Right;
	else if (MousePositionY == 0)
		return MouseScrollDirection = EMouseScrollDirection::Top;
	else if (MousePositionY == ActiveViewportSize.Y)
		return MouseScrollDirection = EMouseScrollDirection::Bottom; 

	return MouseScrollDirection = EMouseScrollDirection::Centre; 
}

void ACameraPawn::InitializeActiveViewport(FVector2D const& ViewportSize, int32 const MouseCursorSize)
{
	ActiveViewportSize.X = FMath::TruncToInt(ViewportSize.X) - MouseCursorSize; 
	ActiveViewportSize.Y = FMath::TruncToInt(ViewportSize.Y) - MouseCursorSize; 
}
