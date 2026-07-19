// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UHealthComponent::ApplyDamage(float Damage)
{
	if (IsDead())
		return;

	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health, MaxHealth);
	if (IsDead())
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			2.f,
			FColor::Red,
			TEXT("Broadcasting OnDeath"));
		OnDeath.Broadcast();
	}
}

void UHealthComponent::Heal(float Amount)
{
	Health = FMath::Clamp(Health + Amount, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health, MaxHealth);
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	
}
