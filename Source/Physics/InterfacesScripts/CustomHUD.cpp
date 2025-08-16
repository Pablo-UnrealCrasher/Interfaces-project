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
	
	if (HeaderUserWidgetClass)
	{
		HeaderUserWidget = CreateWidget(PlayerController, HeaderUserWidgetClass, FName(TEXT("HeaderUserWidget")));
		HeaderUserWidget->AddToViewport();
	}
	if (UpgradeMenuUserWidgetClass)
	{
		UpgradeMenuUserWidget = CreateWidget(PlayerController, UpgradeMenuUserWidgetClass, FName(TEXT("UpgradeMenuUserWidget")));
		UpgradeMenuUserWidget->AddToViewport();
	}
}
