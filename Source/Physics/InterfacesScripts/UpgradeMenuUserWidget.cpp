// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeMenuUserWidget.h"

#include "UpgradesRow.h"
#include "Components/Border.h"

void UUpgradeMenuUserWidget::DisplayNoPointsWarning()
{
	if (!IsValid(NoPointsWarningBorder))
	{
		return;
	}

	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	// We deactivate a previous Timer if there was one.
	if (NoPointsWarningTimerHandle.IsValid() && TimerManager.IsTimerActive(NoPointsWarningTimerHandle))
	{
		TimerManager.ClearTimer(NoPointsWarningTimerHandle);
	}
	
	// We activate our new Timer.
	TimerManager.SetTimer(NoPointsWarningTimerHandle, this, &UUpgradeMenuUserWidget::HideNoPointsWarning, 2.f);

	// We show our warning.
	NoPointsWarningBorder->SetVisibility(ESlateVisibility::Visible);
}

void UUpgradeMenuUserWidget::HideNoPointsWarning()
{
	if (!IsValid(NoPointsWarningBorder))
	{
		return;
	}

	NoPointsWarningBorder->SetVisibility(ESlateVisibility::Hidden);
}

void UUpgradeMenuUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (IsValid(UpgradesRow0))                                
	{
		UpgradesRow0->OnUpgradeFailed.BindUFunction(this, FName(TEXT("DisplayNoPointsWarning")));
	}
	if (IsValid(UpgradesRow1))                                
	{
		UpgradesRow1->OnUpgradeFailed.BindUFunction(this, FName(TEXT("DisplayNoPointsWarning")));
	}
	if (IsValid(UpgradesRow2))
	{
		UpgradesRow2->OnUpgradeFailed.BindUFunction(this, FName(TEXT("DisplayNoPointsWarning")));
	}

	HideNoPointsWarning();
}
