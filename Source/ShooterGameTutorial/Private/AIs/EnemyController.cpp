// Fill out your copyright notice in the Description page of Project Settings.


#include "AIs/EnemyController.h"

#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AEnemyController::AEnemyController()
{
	ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeObject(TEXT("/Game/AI/BT_EnemyBehavior.BT_EnemyBehavior"));
	if(BehaviorTreeObject.Succeeded())
		BehaviorTree = BehaviorTreeObject.Object;

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(FName("Perception Component"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(FName("Sight Config"));

	SightConfig->SightRadius = 500;
	SightConfig->LoseSightRadius = 1000;
	SightConfig->PeripheralVisionAngleDegrees = 60;

	AIPerceptionComponent->ConfigureSense(*SightConfig);

	SetGenericTeamId(FGenericTeamId(1));
}


void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerPawn = UGameplayStatics::GetPlayerPawn(this,0);

	RunBehaviorTree(BehaviorTree);

	GetBlackboardComponent()->SetValueAsVector(FName("Destination"),PlayerPawn->GetActorLocation());
	
	/*MoveToActor(PlayerPawn);
	SetFocus(PlayerPawn,EAIFocusPriority::Gameplay);*/
	
}

void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(LineOfSightTo(PlayerPawn))
	{
		GetBlackboardComponent()->SetValueAsObject(FName("Player"),PlayerPawn);
	}
	else
	{
		GetBlackboardComponent()->ClearValue(FName("Player"));
	}
}


