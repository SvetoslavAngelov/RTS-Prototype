// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatManager.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Public/PlayerControllers/LatePlayerController.h"
#include "Public/Units/UnitBase.h"

UCombatManager::UCombatManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UCombatManager::AttackUnit(AUnitBase* Unit)
{
	if (Unit)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Unit->GetName());
	}
}