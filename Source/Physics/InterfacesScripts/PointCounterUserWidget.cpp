// Fill out your copyright notice in the Description page of Project Settings.


#include "PointCounterUserWidget.h"

#include "PhysicsGameMode.h"
#include "Components/TextBlock.h"

void UPointCounterUserWidget::SetNewPointCount(const int NewPoints)
{
	if (!IsValid(TextBlock) || NewPoints < 0)
	{
		return;
	}

	const FString NewText = POINTS_TEXT + FString::FromInt(NewPoints);
	TextBlock->SetText(FText::FromString(NewText));
}

bool UPointCounterUserWidget::Initialize()
{
	bool bResult = Super::Initialize();

	UWorld* World = GetWorld();
	if (IsValid(World))
	{
		APhysicsGameMode* GameMode = Cast<APhysicsGameMode>(World->GetAuthGameMode());
		if (IsValid(GameMode))
		{
			GameMode->OnPointCountChange.AddDynamic(this, &UPointCounterUserWidget::SetNewPointCount);
		}
	}

	return bResult;
}
