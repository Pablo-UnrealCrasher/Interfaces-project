// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UpgradeButton.generated.h"

class APhysicsGameMode;
class UImage;
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
	const float TIME_NO_POINTS_IMAGE_IS_VISIBLE_FOR = 1.3f;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* UpgradeButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UProgressBar* UpgradeProgressBar;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UImage* LockedUpgradeImage;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UImage* NoPointsImage;

protected:
	UPROPERTY(EditAnywhere, Category = "Appearance")
	UTexture2D* UpgradeIcon;

private:
	bool bUpgradeObtained = false;
	bool bButtonPressed = false;
	float TotalTimePressingButton = 0.0f;
	float TimeLeftOfNoPointsImageVisible = 0.0f;

	UPROPERTY()
	APhysicsGameMode* PhysicsGameMode;
	
	FVector2D OriginalRenderScale;

public:
	FUpgradeObtained OnUpgradeObtained;

	UFUNCTION()
	void UnlockUpgrade();
	
private:
	UFUNCTION()
	void OnButtonPressed();
	UFUNCTION()
	void OnButtonReleased();

	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void SynchronizeProperties() override;
};
