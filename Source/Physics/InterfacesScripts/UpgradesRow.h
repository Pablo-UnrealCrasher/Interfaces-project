// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UpgradeButton.h"
#include "UpgradesRow.generated.h"

class UTextBlock;
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

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UTextBlock* UpgradeAlreadyObtainedText;
	
	int LastUnlockedUpgrade = 0;

	FTimerHandle UpgradeAlreadyObtainedTimerHandle;

public:
	FUpgradeFailed OnUpgradeFailed;

private:
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void OnUpgradeUnlocked();

	UFUNCTION()
	void ShowUpgradeAlreadyObtainedMessage();

	UFUNCTION()
	void HideUpgradeAlreadyObtainedMessage();

	UFUNCTION()
	void SubButtonUpgradeFailed();

	UUpgradeButton* GetUpgradeButton(const int UpgradeButtonNumber) const;
};
