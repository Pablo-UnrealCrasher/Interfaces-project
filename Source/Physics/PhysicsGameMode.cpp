// Copyright Epic Games, Inc. All Rights Reserved.

#include "PhysicsGameMode.h"
#include "UObject/ConstructorHelpers.h"

APhysicsGameMode::APhysicsGameMode() : Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}

void APhysicsGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void APhysicsGameMode::SetPointCount(const int NewPointCount)
{
	if (NewPointCount == PointCount)
	{
		return;
	}

	PointCount = NewPointCount;
	OnPointCountChange.Broadcast(PointCount);
}

int APhysicsGameMode::GetPointCount() const
{
	return PointCount;
}
