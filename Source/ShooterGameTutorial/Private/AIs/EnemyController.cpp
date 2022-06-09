// Fill out your copyright notice in the Description page of Project Settings.


#include "AIs/EnemyController.h"

#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "BehaviorTree/BehaviorTree.h"

AEnemyController::AEnemyController()
{
	ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeObject(TEXT("/Game/AI/BT_EnemyBehavior.BT_EnemyBehavior"));
	if(BehaviorTreeObject.Succeeded())
		BehaviorTree = BehaviorTreeObject.Object;
}


void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this,0);

	RunBehaviorTree(BehaviorTree);

	/*MoveToActor(PlayerPawn);

	SetFocus(PlayerPawn,EAIFocusPriority::Gameplay);*/
	
}

void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


