// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "MainController.generated.h"

class ACustomHUD;
class UPhysicsWeaponComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpgradeMenuStateChange, bool, bIsUpgradeOpen);

class UInputMappingContext;
class UInputAction;
class UInputMappingContext;
class UEnhancedInputLocalPlayerSubsystem;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class PHYSICS_API AMainController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputMappingContext* BaseInputMappingContext;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputMappingContext* WeaponInputMappingContext;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputMappingContext* UpgradeMenuInputMappingContext;

	/** ToggleUpgradeMenu Input Action */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* ToggleUpgradeMenuAction;

	/** Fire Input Action */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* FireAction;
	
	UPROPERTY()
	bool bHasPickedUpWeapon = false;
	UPROPERTY()
	bool bIsUpgradeMenuOpen = false;

	UPROPERTY()
	ACustomHUD* CustomHUD;

public:
	FUpgradeMenuStateChange OnUpgradeMenuStateChange;
	
	void NotifyPickedUpWeapon(UPhysicsWeaponComponent* PhysicsWeaponComponent);
	void NotifyToggleUpgradeMenu(const FInputActionValue& Value);

	auto ToggleInputMappingContext(UEnhancedInputLocalPlayerSubsystem* Subsystem, const UInputMappingContext* IMC_Class, const bool bIsEnabled) -> void;

	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;
};
