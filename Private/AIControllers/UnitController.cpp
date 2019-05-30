// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/AIControllers/UnitController.h"
#include "Runtime/NavigationSystem/Public/NavigationData.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"

TArray<FVector> AUnitController::BuildUnitPath(FAIMoveRequest const& MoveRequest)
{
	TArray<FVector> Result;
	FNavPathSharedPtr OutPath;
	FPathFindingQuery Query;
	BuildPathfindingQuery(MoveRequest, Query);
	FindPathForMoveRequest(MoveRequest, Query, OutPath);
	if (OutPath.IsValid())
	{
		for (auto Point : OutPath.Get()->GetPathPoints())
		{
			Result.Add(Point.Location);
		}
	}
	return Result;
}