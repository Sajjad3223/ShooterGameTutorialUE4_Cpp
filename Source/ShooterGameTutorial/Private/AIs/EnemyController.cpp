// Fill out your copyright notice in the Description page of Project Settings.


#include "AIs/EnemyController.h"

AEnemyController::AEnemyController()
{
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp,Warning,TEXT("This pawn is conrolled by EnemyController"));
}

void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


