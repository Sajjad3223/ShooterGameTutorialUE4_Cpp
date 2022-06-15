// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameMode.h"

#include "EngineUtils.h"
#include "AIs/EnemyController.h"
#include "Characters/SajjadComando.h"
#include "ShooterPlayerController.h"

AShooterGameMode::AShooterGameMode() {
	DefaultPawnClass = ASajjadComando::StaticClass();
	PlayerControllerClass = AShooterPlayerController::StaticClass();
}

void AShooterGameMode::HandleKills(APawn* PawnKilled) {
	AController* Controller = PawnKilled->GetController();

	//Cast to Player Controller
	APlayerController* PlayerController = Cast<APlayerController>(Controller);

	//If Cast was Successful The pawn is the player
	if (PlayerController != nullptr) {
		PlayerController->GameHasEnded(nullptr, false);
	}

	// If not it is an enemy
	// If so Check how many enemies remaining
	for (AEnemyController* Enemy : TActorRange<AEnemyController>(GetWorld())) {
		// If Enemy Not Dead -> Return
		if (!Enemy->IsEnemyDead()) return;
	}

	PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->GameHasEnded(nullptr, true);
}