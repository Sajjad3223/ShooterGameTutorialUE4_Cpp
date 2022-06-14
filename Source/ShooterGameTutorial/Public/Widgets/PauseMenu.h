// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
class UButton;
class AShooterPlayerController;

UCLASS()
class SHOOTERGAMETUTORIAL_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;

	void SetupController(AShooterPlayerController* playerController);

private:
	UFUNCTION()
	void ResumeGame();
	UFUNCTION()
	void RestartGame();
	UFUNCTION()
	void QuitGame();

	UPROPERTY(meta = (BindWidget))
	UButton* Resume;

	UPROPERTY(meta = (BindWidget))
	UButton* Restart;

	UPROPERTY(meta = (BindWidget))
	UButton* Quit;

	AShooterPlayerController* PlayerController = nullptr;
};
