// Copyright Epic Games, Inc. All Rights Reserved.


#include "PhysicsWeaponComponent.h"
#include "PhysicsCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MainController.h"
#include "Animation/AnimInstance.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UPhysicsWeaponComponent::UPhysicsWeaponComponent()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);

}

void UPhysicsWeaponComponent::Fire()
{
	if (!IsValid(Character) || Character->GetController() == nullptr)
	{
		return;
	}
	
	// Try and play the sound if specified
	if (IsValid(FireSound))
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}
	
	// Try and play a firing animation if specified
	if (IsValid(FireAnimation))
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (IsValid(AnimInstance))
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

bool UPhysicsWeaponComponent::AttachWeapon(APhysicsCharacter* TargetCharacter)
{
	// Check that the character is valid, and has no weapon component yet
	if (!IsValid(TargetCharacter) || TargetCharacter->GetInstanceComponents().FindItemByClass<UPhysicsWeaponComponent>())
	{
		return false;
	}
	
	Character = TargetCharacter;

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));

	// Set up action bindings
	AMainController* PlayerController = Cast<AMainController>(Character->GetController());
	if (IsValid(PlayerController))
	{
		PlayerController->NotifyPickedUpWeapon(this);
	}

	return true;
}

void UPhysicsWeaponComponent::ApplyDamage(const FHitResult& HitResult) const
{
	if (!IsValid(Character) || !IsValid(m_WeaponDamageType))
	{
		return;
	}
	
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

	if (IsValid(m_FsMasterField))
	{
		GetWorld()->SpawnActor(m_FsMasterField, &FsMasterFieldTransform, FActorSpawnParameters());
	}
}
