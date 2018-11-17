// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
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
	void MoveLeft() const;
	void MoveRight() const;
	void MoveForward() const;
	void MoveBackward() const;

	// Movement component
	UPROPERTY(VisibleAnywhere)
	class UCameraPawnMovementComponent* MovementComponent;

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
};
