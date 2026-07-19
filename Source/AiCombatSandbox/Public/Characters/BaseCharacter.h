// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UHealthComponent;
class UCombatComponent;
class UAnimMontage;

UCLASS()
class AICOMBATSANDBOX_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnDeath();

	virtual void Die();

	UFUNCTION(BlueprintNativeEvent, Category = "Animation")
	void PlayAttackAnimation();

	virtual void PlayHitReaction();

	//virtual void InitializeAbilities();

public:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHealthComponent> HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCombatComponent> CombatComponent;

public:

	virtual void Attack();
	virtual void ReciveDamage(float Damage);

	FORCEINLINE UHealthComponent* GetHealthComponent() const
	{
		return HealthComponent;
	}

	FORCEINLINE UCombatComponent* GetCombatComponent() const
	{
		return CombatComponent;
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aniamtion")
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aniamtion")
	TObjectPtr<UAnimMontage> HitReactionMontage;

};