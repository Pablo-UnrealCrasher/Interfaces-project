// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "CustomHUD.generated.h"

/**
 * 
 */
UCLASS()
class PHYSICS_API ACustomHUD : public AHUD
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
	TSubclassOf<UUserWidget> HeaderUserWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
	TSubclassOf<UUserWidget> UpgradeMenuUserWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
	TSubclassOf<UUserWidget> PointCounterUserWidgetClass;
	
	UPROPERTY()
	UUserWidget* HeaderUserWidget;
	
	UPROPERTY()
	UUserWidget* UpgradeMenuUserWidget;

	UPROPERTY()
	UUserWidget* PointCounterUserWidget;
	
	virtual void BeginPlay() override;

public:
	void ShowUpgradeMenu();
	void HideUpgradeMenu();
};
