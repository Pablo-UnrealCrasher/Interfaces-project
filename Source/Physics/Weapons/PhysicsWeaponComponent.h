// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponDamageType.h"
#include "PhysicsWeaponComponent.generated.h"

class APhysicsCharacter;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PHYSICS_API UPhysicsWeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector MuzzleOffset;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	/** Weapon damage config*/
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category=Damage, meta=(AllowPrivateAccess = "true"))
	UWeaponDamageType* m_WeaponDamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Damage)
	TSubclassOf<AActor> m_FsMasterField;

	/** Sets default values for this component's properties */
	UPhysicsWeaponComponent();	

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	bool AttachWeapon(APhysicsCharacter* TargetCharacter);

	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	virtual void Fire();

protected:

	/** Ends gameplay for this component. */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	/** The Character holding this weapon*/
	APhysicsCharacter* Character;

	UFUNCTION()
	void ApplyDamage(const FHitResult& HitResult) const;
};
