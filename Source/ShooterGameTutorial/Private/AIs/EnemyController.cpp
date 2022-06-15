// Fill out your copyright notice in the Description page of Project Settings.


#include "AIs/EnemyController.h"

#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Characters/SajjadComando.h"
#include "ShooterPlayerController.h"

AEnemyController::AEnemyController()
{
	ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeObject(TEXT("/Game/AI/BT_EnemyBehavior.BT_EnemyBehavior"));
	if(BehaviorTreeObject.Succeeded())
		BehaviorTree = BehaviorTreeObject.Object;

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(FName("Perception Component"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(FName("Sight Config"));
	
	SightConfig->SightRadius = 800;
	SightConfig->LoseSightRadius = 1000;
	SightConfig->PeripheralVisionAngleDegrees = 70;

	AIPerceptionComponent->ConfigureSense(*SightConfig);

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this,&AEnemyController::OnPlayerSeen);

	SetGenericTeamId(FGenericTeamId(5));
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);

	GetBlackboardComponent()->SetValueAsVector(FName("StartLocation"),GetPawn()->GetActorLocation());	
}

void AEnemyController::OnPlayerSeen(AActor* Actor, FAIStimulus Stimulus)
{
	ASajjadComando* PlayerCharacter = Cast<ASajjadComando>(Actor);
	AShooterPlayerController* PlayerController = Cast<AShooterPlayerController>(PlayerCharacter->GetController());
	if (PlayerController == nullptr) return;
	if(Stimulus.WasSuccessfullySensed())
	{
		SetFocus(Actor);
		GetBlackboardComponent()->SetValueAsObject(FName("Player"),Actor);
	}
	else
	{
		ClearFocus(EAIFocusPriority::Gameplay);
		GetBlackboardComponent()->SetValueAsVector(FName("LastSeenLocation"), Actor->GetActorLocation());
		GetBlackboardComponent()->ClearValue(FName("Player"));
	}
}

bool AEnemyController::IsEnemyDead() {
	APawn* ControllerPawn = GetPawn();
	ASajjadComando* PlayerCharacter = Cast<ASajjadComando>(ControllerPawn);

	return PlayerCharacter->GetHealth() <= 0;
}
