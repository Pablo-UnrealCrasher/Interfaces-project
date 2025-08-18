// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradesRow.h"

#include "Components/TextBlock.h"

void UUpgradesRow::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// Activating our First Button.
	UUpgradeButton* FirstUpgradeButton = GetUpgradeButton(0);
	if (IsValid(FirstUpgradeButton))
	{
		FirstUpgradeButton->UnlockUpgrade();
		FirstUpgradeButton->OnUpgradeObtained.BindUFunction(this, FName(TEXT("OnUpgradeUnlocked")));
		FirstUpgradeButton->OnUpgradeFailed.BindUFunction(this, FName(TEXT("SubButtonUpgradeFailed")));
	}

	HideUpgradeAlreadyObtainedMessage();
}

void UUpgradesRow::OnUpgradeUnlocked()
{
	UUpgradeButton* CurrentUpgradeButton = GetUpgradeButton(LastUnlockedUpgrade);
	LastUnlockedUpgrade++;
	UUpgradeButton* NextUpgradeButton = GetUpgradeButton(LastUnlockedUpgrade);
	
	if (IsValid(CurrentUpgradeButton))
	{
		CurrentUpgradeButton->OnUpgradeObtained.Unbind();
		CurrentUpgradeButton->OnUpgradeFailed.Unbind();
		
		CurrentUpgradeButton->OnUpgradeAlreadyObtained.BindUFunction(this, FName(TEXT("ShowUpgradeAlreadyObtainedMessage")));
	}
	
	if (IsValid(NextUpgradeButton))
	{
		NextUpgradeButton->UnlockUpgrade();
		NextUpgradeButton->OnUpgradeObtained.BindUFunction(this, FName(TEXT("OnUpgradeUnlocked")));
		NextUpgradeButton->OnUpgradeFailed.BindUFunction(this, FName(TEXT("SubButtonUpgradeFailed")));
	}
}

void UUpgradesRow::ShowUpgradeAlreadyObtainedMessage()
{
	if (!IsValid(UpgradeAlreadyObtainedText))
	{
		return;
	}

	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	// We deactivate a previous Timer if there was one.
	if (UpgradeAlreadyObtainedTimerHandle.IsValid() && TimerManager.IsTimerActive(UpgradeAlreadyObtainedTimerHandle))
	{
		TimerManager.ClearTimer(UpgradeAlreadyObtainedTimerHandle);
	}
	
	// We activate our new Timer.
	TimerManager.SetTimer(UpgradeAlreadyObtainedTimerHandle, this, &UUpgradesRow::HideUpgradeAlreadyObtainedMessage, 2.f);

	UpgradeAlreadyObtainedText->SetVisibility(ESlateVisibility::Visible);
}

void UUpgradesRow::HideUpgradeAlreadyObtainedMessage()
{
	if (!IsValid(UpgradeAlreadyObtainedText))
	{
		return;
	}

	UpgradeAlreadyObtainedText->SetVisibility(ESlateVisibility::Hidden);
}

void UUpgradesRow::SubButtonUpgradeFailed()
{
	OnUpgradeFailed.ExecuteIfBound();
}

UUpgradeButton* UUpgradesRow::GetUpgradeButton(const int UpgradeButtonNumber) const
{
	switch (UpgradeButtonNumber)
	{
	case 0:
		return UpgradeButton0;
	case 1:
		return UpgradeButton1;
	case 2:
		return UpgradeButton2;
		
	default:
		return nullptr;
	}
}
