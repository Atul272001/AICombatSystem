// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, CurrentHealth, float, MaxHealth);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AICOMBATSANDBOX_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UFUNCTION(BlueprintCallable)
	void ApplyDamage(float Damage);

	UFUNCTION(BlueprintCallable)
	void Heal(float Amount);

	UFUNCTION(BlueprintPure, Category = "Health")
	FORCEINLINE float GetHealth() const
	{
		return Health;
	}

	UFUNCTION(BlueprintPure, Category = "Health")
	FORCEINLINE float GetMaxHealth() const
	{
		return MaxHealth;
	}

	FORCEINLINE bool IsDead() const
	{
		return Health <= 0.0f;
	}

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDeath OnDeath;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChanged OnHealthChanged;

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "Health")
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Health")
	float Health = 100.0f;
};
