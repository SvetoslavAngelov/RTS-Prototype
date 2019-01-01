// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Public/Data/MouseScrollDirection.h"
#include "CameraPawn.generated.h"

UCLASS()
class LATE_API ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual class UPawnMovementComponent* GetMovementComponent() const override;

	// Camera movement interface
	void UpdateCameraPosition() const;

	EMouseScrollDirection GetMouseScrollDirection() const; 

	EMouseScrollDirection SetMouseScrollDirection(int32 const MousePositionX, int32 const MousePositionY);

	void InitializeActiveViewport(FVector2D const& ViewportSize, int32 const MouseCursorSize);

private:
	// Pawn root
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereComponent;

	// Spring arm component
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	// Camera actor 
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	// Movement component
	UPROPERTY(VisibleAnywhere)
	class UCameraPawnMovementComponent* MovementComponent;

	// Camera scroll speed 
	UPROPERTY()
	float CameraScrollSpeed;

	// Enum mouse screen position
	UPROPERTY()
	EMouseScrollDirection MouseScrollDirection; 
	
	// Active viewport 
	UPROPERTY()
	FVector2D ActiveViewportSize; 
};
