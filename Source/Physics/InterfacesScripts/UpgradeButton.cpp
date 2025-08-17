// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeButton.h"

#include "Components/Button.h"
#include "Components/ProgressBar.h"

void UUpgradeButton::OnButtonPressed()
{
	bButtonPressed = true;
	UpgradeButton->SetRenderScale(OriginalRenderScale * 0.95f);
}

void UUpgradeButton::OnButtonReleased()
{
	bButtonPressed = false;
	TotalTimePressingButton = 0.0f;
	UpgradeButton->SetRenderScale(OriginalRenderScale);
}

void UUpgradeButton::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UpdateCanTick();
	
	if (IsValid(UpgradeButton))
	{
		UpgradeButton->OnPressed.AddDynamic(this, &UUpgradeButton::OnButtonPressed);
		UpgradeButton->OnReleased.AddDynamic(this, &UUpgradeButton::OnButtonReleased);
		OriginalRenderScale = UpgradeButton->GetRenderTransform().Scale;
	}

	if (IsValid(UpgradeProgressBar))
	{
		UpgradeProgressBar->SetPercent(0);
	}

	UE_LOG(LogViewport, Warning, TEXT("Initialized"));
}

void UUpgradeButton::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (bUpgradeObtained || !bButtonPressed || !IsValid(UpgradeButton))
	{
		return;
	}
	
	TotalTimePressingButton += InDeltaTime;
	const float PercentageHeldCompleted = FMath::Square(TotalTimePressingButton / TIME_REQUIRED_TO_UPGRADE);

	if (PercentageHeldCompleted > 1.0f)
	{
		bUpgradeObtained = true;
		OnUpgradeObtained.ExecuteIfBound();
		UpgradeButton->SetIsEnabled(false);
		UpgradeButton->SetRenderScale(OriginalRenderScale);

		if (IsValid(UpgradeProgressBar))
		{
			UpgradeProgressBar->SetPercent(0);
		}
	}
	else if (IsValid(UpgradeProgressBar))
	{
		UpgradeProgressBar->SetPercent(PercentageHeldCompleted);
	}
}
