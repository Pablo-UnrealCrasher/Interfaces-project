// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeButton.h"

#include "PhysicsGameMode.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"

void UUpgradeButton::UnlockUpgrade()
{
	if (IsValid(LockedUpgradeImage))
	{
		LockedUpgradeImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UUpgradeButton::OnButtonPressed()
{
	bButtonPressed = true;

	if (IsValid(UpgradeButton))
	{
		UpgradeButton->SetRenderScale(OriginalRenderScale * 0.95f);
	}
}

void UUpgradeButton::OnButtonReleased()
{
	if (!bButtonPressed)
	{
		return;
	}
	
	bButtonPressed = false;
	TotalTimePressingButton = 0.0f;
	
	if (IsValid(UpgradeButton))
	{
		UpgradeButton->SetRenderScale(OriginalRenderScale);
	}

	if (IsValid(UpgradeProgressBar))
	{
		UpgradeProgressBar->SetPercent(0);
	}
}

void UUpgradeButton::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
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

	UWorld* World = GetWorld();
	if (IsValid(World))
	{
		PhysicsGameMode = Cast<APhysicsGameMode>(World->GetAuthGameMode());
	}
}

void UUpgradeButton::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// If we are currently showcasing a No Points Image.
	if (TimeLeftOfNoPointsImageVisible > 0.0f)
	{
		TimeLeftOfNoPointsImageVisible -= InDeltaTime;

		if (TimeLeftOfNoPointsImageVisible <= 0.0f)
		{
			NoPointsImage->SetVisibility(ESlateVisibility::Hidden);
			TimeLeftOfNoPointsImageVisible = 0.0f;
		}

		return;
	}
	
	if (bUpgradeObtained || !bButtonPressed || !IsValid(UpgradeButton))
	{
		return;
	}
	
	TotalTimePressingButton += InDeltaTime;
	const float PercentageHeldCompleted = FMath::Square(TotalTimePressingButton / TIME_REQUIRED_TO_UPGRADE);

	if (PercentageHeldCompleted > 1.0f)
	{
		bButtonPressed = false;
		UpgradeButton->SetRenderScale(OriginalRenderScale);
		TotalTimePressingButton = 0.0f;

		// Resetting the Progress Bar.
		if (IsValid(UpgradeProgressBar))
		{
			UpgradeProgressBar->SetPercent(0);
		}
		
		// Checking if we have enough points for the Upgrade.
		if (!IsValid(PhysicsGameMode) || PhysicsGameMode->GetPointCount() <= 0)
		{
			NoPointsImage->SetVisibility(ESlateVisibility::Visible);
			TimeLeftOfNoPointsImageVisible = TIME_NO_POINTS_IMAGE_IS_VISIBLE_FOR;
			return;
		}

		PhysicsGameMode->SetPointCount(PhysicsGameMode->GetPointCount() - 1);
		bUpgradeObtained = true;
		UpgradeButton->SetIsEnabled(false);
		OnUpgradeObtained.ExecuteIfBound();
	}
	else if (IsValid(UpgradeProgressBar))
	{
		UpgradeProgressBar->SetPercent(PercentageHeldCompleted);
	}
}

void UUpgradeButton::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (IsValid(UpgradeButton) && IsValid(UpgradeIcon))
	{
		FButtonStyle NewStyle = UpgradeButton->GetStyle();
		NewStyle.Normal.SetResourceObject(UpgradeIcon);
		NewStyle.Normal.SetImageSize(FVector2D(UpgradeIcon->GetSizeX(), UpgradeIcon->GetSizeY()));
		NewStyle.Disabled.SetResourceObject(UpgradeIcon);
		NewStyle.Disabled.SetImageSize(FVector2D(UpgradeIcon->GetSizeX(), UpgradeIcon->GetSizeY()));
		NewStyle.Hovered.SetResourceObject(UpgradeIcon);
		NewStyle.Hovered.SetImageSize(FVector2D(UpgradeIcon->GetSizeX(), UpgradeIcon->GetSizeY()));
		NewStyle.Pressed.SetResourceObject(UpgradeIcon);
		NewStyle.Pressed.SetImageSize(FVector2D(UpgradeIcon->GetSizeX(), UpgradeIcon->GetSizeY()));
		UpgradeButton->SetStyle(NewStyle);
	}
}
