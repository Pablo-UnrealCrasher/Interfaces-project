// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UpgradeMenuUserWidget.generated.h"

class UBorder;
class UUpgradesRow;
class UImage;

/**
 * 
 */
UCLASS()
class PHYSICS_API UUpgradeMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UBorder* NoPointsWarningBorder;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UUpgradesRow* UpgradesRow0;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UUpgradesRow* UpgradesRow1;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UUpgradesRow* UpgradesRow2;

	FTimerHandle NoPointsWarningTimerHandle;

	UFUNCTION()
	void DisplayNoPointsWarning();

	UFUNCTION()
	void HideNoPointsWarning();

	virtual void NativeOnInitialized() override;
};
