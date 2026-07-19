// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_Attack.h"
#include "AIController.h"
#include "Characters/BaseCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if(!AIController)
		return EBTNodeResult::Failed;

	ABaseCharacter* Character = Cast<ABaseCharacter>(AIController->GetPawn());

	if(!Character)
		return EBTNodeResult::Failed;

	Character->Attack();

	return EBTNodeResult::Succeeded;;
}
