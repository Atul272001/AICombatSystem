// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

class ABaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AICOMBATSANDBOX_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void PerformAttack();

private:

	UPROPERTY()
	TObjectPtr<ABaseCharacter> OwnerCharacter;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float BaseDamage = 25.0f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackRange = 200.0f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackRadius = 50.0f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackCooldown = 2.0f;

	FTimerHandle AttackCooldownTimer;

public:
	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool CanAttack() const;
	void ResetAttack();
};
