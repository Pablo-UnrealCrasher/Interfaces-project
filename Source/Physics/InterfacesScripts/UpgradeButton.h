// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UpgradeButton.generated.h"

DECLARE_DYNAMIC_DELEGATE(FUpgradeObtained);

class UButton;
class UProgressBar;
/**
 * 
 */
UCLASS()
class PHYSICS_API UUpgradeButton : public UUserWidget
{
	GENERATED_BODY()

	const float TIME_REQUIRED_TO_UPGRADE = 1.0f;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* UpgradeButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UProgressBar* UpgradeProgressBar;

	bool bUpgradeObtained = false;
	bool bButtonPressed = false;
	float TotalTimePressingButton = 0.0f;

	FVector2D OriginalRenderScale;

public:
	FUpgradeObtained OnUpgradeObtained;
	
private:
	UFUNCTION()
	void OnButtonPressed();
	UFUNCTION()
	void OnButtonReleased();

	virtual void NativeOnInitialized() override;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
