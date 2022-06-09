// Fill out your copyright notice in the Description page of Project Settings.


#include "AIs/EnemyController.h"

#include "Kismet/GameplayStatics.h"

AEnemyController::AEnemyController()
{
}


void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp,Warning,TEXT("This pawn is conrolled by EnemyController"));

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this,0);

	MoveToLocation(FVector(1303,700,145));

	SetFocus(PlayerPawn,EAIFocusPriority::Gameplay);
	
}

void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


