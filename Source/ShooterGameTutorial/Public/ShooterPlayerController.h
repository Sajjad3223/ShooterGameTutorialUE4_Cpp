// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAMETUTORIAL_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AShooterPlayerController();

	void ResumeGame();
	void RestartGame();
	void QuitGame();

	virtual void GameHasEnded(AActor* EndGameFocus, bool bIsWinner) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
private:

	void PauseAndSetupWidget(class URestartableAndQuitable* Widget);

	TSubclassOf<class UPlayerHud> PlayerHudClass;
	TSubclassOf<class UPauseMenu> PauseMenuClass;
	TSubclassOf<class UEndGame> EndGameClass;

	UFUNCTION()
	void PauseGame();
};
