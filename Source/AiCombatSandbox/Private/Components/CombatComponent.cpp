// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CombatComponent.h"
#include "Characters/BaseCharacter.h"
#include "Components/HealthComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ABaseCharacter>(GetOwner());
}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCombatComponent::PerformAttack()
{
	if (!CanAttack())
		return;


	GetWorld()->GetTimerManager().SetTimer(AttackCooldownTimer, this, &UCombatComponent::ResetAttack, AttackCooldown, false);

	if (!OwnerCharacter)
		return;

	const FVector Start = OwnerCharacter->GetActorLocation();
	const FVector End = Start + OwnerCharacter->GetActorForwardVector() * AttackRange;

	FHitResult Hit;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(OwnerCharacter);

	const bool bHit = GetWorld()->SweepSingleByChannel(Hit, Start, End, FQuat::Identity, ECC_Pawn, FCollisionShape::MakeSphere(AttackRadius), Params);
	DrawDebugSphere(GetWorld(), End, AttackRadius, 16, bHit ? FColor::Red : FColor::Green, false, 2.0f);

	if (!bHit)
		return;

	ABaseCharacter* HitCharacter = Cast<ABaseCharacter>(Hit.GetActor());

	if (HitCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Applying Damage"));
		HitCharacter->ReciveDamage(BaseDamage);
	}

}

bool UCombatComponent::CanAttack() const
{
	return !GetWorld()->GetTimerManager().IsTimerActive(AttackCooldownTimer);
}

void UCombatComponent::ResetAttack()
{
	//bCanAttack = true;
}
