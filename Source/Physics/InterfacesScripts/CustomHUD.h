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
	
	UPROPERTY()
	UUserWidget* HeaderUserWidget;
	
	UPROPERTY()
	UUserWidget* UpgradeMenuUserWidget;
	
	virtual void BeginPlay() override;
};
