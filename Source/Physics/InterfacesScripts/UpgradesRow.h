// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UpgradesRow.generated.h"

class UUpgradeButton;
/**
 * 
 */
UCLASS()
class PHYSICS_API UUpgradesRow : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UUpgradeButton* UpgradeButton0;
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UUpgradeButton* UpgradeButton1;
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UUpgradeButton* UpgradeButton2;
	
	int LastUnlockedUpgrade = 0;
	
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void OnUpgradeUnlocked();

	UUpgradeButton* GetUpgradeButton(const int UpgradeButtonNumber) const;
};
