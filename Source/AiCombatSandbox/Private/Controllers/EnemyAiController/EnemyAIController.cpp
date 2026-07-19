// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/EnemyAiController/EnemyAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

namespace BBKeys
{
	const FName TargetActor(TEXT("TargetActor"));
	const FName CanSeePlayer(TEXT("CanSeePlayer"));
}

AEnemyAIController::AEnemyAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	SightConfig->SightRadius = 1500.0f;
	SightConfig->LoseSightRadius = 1700.0f;

	SightConfig->PeripheralVisionAngleDegrees = 70.0f;

	SightConfig->SetMaxAge(3.0f);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetPerceptionUpdated);
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
		PatrolLocation = InPawn->GetActorLocation();
	}
}

void AEnemyAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!GetBlackboardComponent())
	{
		UE_LOG(LogTemp, Error, TEXT("Blackboard is NULL!"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Blackboard is Valid"));
	Blackboard->SetValueAsVector(TEXT("PatrolLocation"), PatrolLocation);

	if (Stimulus.WasSuccessfullySensed())
	{
		GetBlackboardComponent()->SetValueAsObject(BBKeys::TargetActor, Actor);
		GetBlackboardComponent()->SetValueAsBool(BBKeys::CanSeePlayer, true);
	}
	else
	{
		GetBlackboardComponent()->ClearValue(BBKeys::TargetActor);
		GetBlackboardComponent()->SetValueAsBool(BBKeys::CanSeePlayer, false);
	}
}
