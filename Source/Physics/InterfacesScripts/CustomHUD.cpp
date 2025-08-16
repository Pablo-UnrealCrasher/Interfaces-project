// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomHUD.h"

void ACustomHUD::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetOwningPlayerController();
	if (!IsValid(PlayerController))
	{
		return;
	}

	EnableInput(PlayerController);
	
	if (IsValid(HeaderUserWidgetClass))
	{
		HeaderUserWidget = CreateWidget(PlayerController, HeaderUserWidgetClass, FName(TEXT("HeaderUserWidget")));
		HeaderUserWidget->AddToViewport();
	}
	if (IsValid(PointCounterUserWidgetClass))
	{
		PointCounterUserWidget = CreateWidget(PlayerController, PointCounterUserWidgetClass, FName(TEXT("PointCounterUserWidget")));
		PointCounterUserWidget->AddToViewport();
	}
	if (IsValid(UpgradeMenuUserWidgetClass))
	{
		UpgradeMenuUserWidget = CreateWidget(PlayerController, UpgradeMenuUserWidgetClass, FName(TEXT("UpgradeMenuUserWidget")));
	}
}

void ACustomHUD::ShowUpgradeMenu()
{
	if (IsValid(HeaderUserWidget))
	{
		HeaderUserWidget->RemoveFromParent();
	}
	if (IsValid(UpgradeMenuUserWidget))
	{
		UpgradeMenuUserWidget->AddToViewport();
	}
}

void ACustomHUD::HideUpgradeMenu()
{
	if (IsValid(HeaderUserWidget))
	{
		HeaderUserWidget->AddToViewport();
	}
	if (IsValid(UpgradeMenuUserWidget))
	{
		UpgradeMenuUserWidget->RemoveFromParent();
	}
}
