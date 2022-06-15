// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/RestartableAndQuitable.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
class UButton;
class AShooterPlayerController;

UCLASS()
class SHOOTERGAMETUTORIAL_API UPauseMenu : public URestartableAndQuitable
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;

private:
	UFUNCTION()
	void ResumeGame();

	UPROPERTY(meta = (BindWidget))
	UButton* Resume;
};
