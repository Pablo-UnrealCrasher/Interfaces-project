// Copyright Epic Games, Inc. All Rights Reserved.


#include "PhysicsWeaponComponent.h"
#include "PhysicsCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Animation/AnimInstance.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "Field/FieldSystemActor.h"

// Sets default values for this component's properties
UPhysicsWeaponComponent::UPhysicsWeaponComponent()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);

}

void UPhysicsWeaponComponent::Fire()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}
	
	// Try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}
	
	// Try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

bool UPhysicsWeaponComponent::AttachWeapon(APhysicsCharacter* TargetCharacter)
{
	Character = TargetCharacter;

	// Check that the character is valid, and has no weapon component yet
	if (Character == nullptr || Character->GetInstanceComponents().FindItemByClass<UPhysicsWeaponComponent>())
	{
		return false;
	}

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));

	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Fire
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UPhysicsWeaponComponent::Fire);
		}
	}

	return true;
}

void UPhysicsWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// ensure we have a character owner
	if (Character != nullptr)
	{
		// remove the input mapping context from the Player Controller
		if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->RemoveMappingContext(FireMappingContext);
			}
		}
	}

	// maintain the EndPlay call chain
	Super::EndPlay(EndPlayReason);
}

void UPhysicsWeaponComponent::ApplyDamage(const FHitResult& HitResult) const
{
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(Character);
	
	switch (m_WeaponDamageType->ImpulseType)
	{
	case EImpulseType::LINEAR:
		UGameplayStatics::ApplyPointDamage(
			HitResult.GetActor(),
			m_WeaponDamageType->m_Damage,
			-HitResult.Normal,
			HitResult,
			Character->Controller,
			Character,
			m_WeaponDamageType->m_DamageType);
		break;
	case EImpulseType::RADIAL:
		UGameplayStatics::ApplyRadialDamage(
			GetWorld(),
			m_WeaponDamageType->m_Damage,
			HitResult.Location,
			m_WeaponDamageType->m_FalloffRadius,
			m_WeaponDamageType->m_DamageType,
			IgnoreActors,
			Character,
			Character->Controller);
		break;
	case EImpulseType::NONE:
		UGameplayStatics::ApplyDamage(
			HitResult.GetActor(),
			m_WeaponDamageType->m_Damage,
			Character->Controller,
			Character,
			m_WeaponDamageType->m_DamageType);
		break;
	}

	FTransform FsMasterFieldTransform = FTransform((-HitResult.ImpactNormal).Rotation(), HitResult.ImpactPoint, FVector::One());
	GetWorld()->SpawnActor(m_FsMasterField, &FsMasterFieldTransform, FActorSpawnParameters());
}
