// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "Components/HealthComponent.h"
#include "Components/CombatComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnDeath.AddDynamic(this, &ABaseCharacter::OnDeath);	
}

void ABaseCharacter::OnDeath()
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		5.f,
		FColor::Red,
		TEXT("BaseCharacter OnDeath"));
	Die();
}

void ABaseCharacter::Die()
{
}

void ABaseCharacter::PlayAttackAnimation_Implementation()
{
	if (AttackMontage)
	{
		PlayAnimMontage(AttackMontage);
	}
}

void ABaseCharacter::PlayHitReaction()
{
	if (HitReactionMontage)
	{
		PlayAnimMontage(HitReactionMontage);
	}
}

//void ABaseCharacter::InitializeAbilities()
//{
//}

void ABaseCharacter::Attack()
{
	if (!CombatComponent)
		return;

	if (!CombatComponent->CanAttack())
		return;

	PlayAttackAnimation();
}

void ABaseCharacter::ReciveDamage(float Damage)
{
	if (HealthComponent)
	{
		HealthComponent->ApplyDamage(Damage);

		if (!HealthComponent->IsDead())
		{
			PlayHitReaction();
		}
	}
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
