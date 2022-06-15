// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ShooterGameTutorialGameModeBase.h"
#include "ShooterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAMETUTORIAL_API AShooterGameMode : public AShooterGameTutorialGameModeBase
{
	GENERATED_BODY()
public:
	AShooterGameMode();

	void HandleKills(class APawn* KilledPawn);
};
