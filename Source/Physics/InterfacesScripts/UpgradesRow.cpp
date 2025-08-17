// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradesRow.h"

#include "UpgradeButton.h"

void UUpgradesRow::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// Activating our First Button.
	UUpgradeButton* FirstUpgradeButton = GetUpgradeButton(0);
	if (IsValid(FirstUpgradeButton))
	{
		FirstUpgradeButton->UnlockUpgrade();
		FirstUpgradeButton->OnUpgradeObtained.BindUFunction(this, FName(TEXT("OnUpgradeUnlocked")));
	}
}

void UUpgradesRow::OnUpgradeUnlocked()
{
	UUpgradeButton* CurrentUpgradeButton = GetUpgradeButton(LastUnlockedUpgrade);
	LastUnlockedUpgrade++;
	UUpgradeButton* NextUpgradeButton = GetUpgradeButton(LastUnlockedUpgrade);
	
	if (IsValid(CurrentUpgradeButton))
	{
		CurrentUpgradeButton->OnUpgradeObtained.Unbind();
	}
	
	if (IsValid(NextUpgradeButton))
	{
		NextUpgradeButton->UnlockUpgrade();
		NextUpgradeButton->OnUpgradeObtained.BindUFunction(this, FName(TEXT("OnUpgradeUnlocked")));
	}
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
