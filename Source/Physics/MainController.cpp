// Fill out your copyright notice in the Description page of Project Settings.


#include "MainController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InterfacesScripts/CustomHUD.h"
#include "Weapons/PhysicsWeaponComponent.h"

void AMainController::NotifyPickedUpWeapon(UPhysicsWeaponComponent* PhysicsWeaponComponent)
{
	if (bHasPickedUpWeapon || !IsValid(WeaponInputMappingContext))
	{
		return;
	}

	bHasPickedUpWeapon = true;

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (IsValid(EnhancedInputComponent) && IsValid(FireAction) && IsValid(PhysicsWeaponComponent))
	{
		// Binding the Fire Action of the Weapon.
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, PhysicsWeaponComponent, &UPhysicsWeaponComponent::Fire);
	}

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
		Subsystem->AddMappingContext(WeaponInputMappingContext, 1);
	}
}

void AMainController::NotifyToggleUpgradeMenu(const FInputActionValue& Value)
{
	bIsUpgradeMenuOpen = !bIsUpgradeMenuOpen;

	OnUpgradeMenuStateChange.Broadcast(bIsUpgradeMenuOpen);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(Subsystem))
	{
		return;
	}

	// Controlling the Input Maps
	ToggleInputMappingContext(Subsystem, BaseInputMappingContext, !bIsUpgradeMenuOpen);
	ToggleInputMappingContext(Subsystem, UpgradeMenuInputMappingContext, bIsUpgradeMenuOpen);

	if (bHasPickedUpWeapon)
	{
		ToggleInputMappingContext(Subsystem, WeaponInputMappingContext, !bIsUpgradeMenuOpen);
	}

	// Controlling the visible parts of the HUD
	if (IsValid(CustomHUD))
	{
		bIsUpgradeMenuOpen ? CustomHUD->ShowUpgradeMenu() : CustomHUD->HideUpgradeMenu();
	}
}

void AMainController::ToggleInputMappingContext(UEnhancedInputLocalPlayerSubsystem* Subsystem,
	const UInputMappingContext* IMC_Class,
	const bool bIsEnabled)
{
	if (!IsValid(Subsystem) || !IsValid(IMC_Class))
	{
		return;
	}

	if (bIsEnabled)
	{
		Subsystem->AddMappingContext(IMC_Class, 1);
	}
	else
	{
		Subsystem->RemoveMappingContext(IMC_Class);
	}
}

void AMainController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Setting up the Default Input Mapping Context
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (IsValid(Subsystem) && IsValid(BaseInputMappingContext))
	{
		Subsystem->AddMappingContext(BaseInputMappingContext, 0);
	}

	// Binding the ToggleUpgradeMenu Input Action
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInputComponent))
	{
		UE_LOG(LogViewport, Error, TEXT("Failed to SetupInputComponent from MainController."));
		return;
	}

	EnhancedInputComponent->BindAction(ToggleUpgradeMenuAction, ETriggerEvent::Triggered, this, &AMainController::NotifyToggleUpgradeMenu);
}

void AMainController::BeginPlay()
{
	Super::BeginPlay();

	CustomHUD = Cast<ACustomHUD>(GetHUD());
}
