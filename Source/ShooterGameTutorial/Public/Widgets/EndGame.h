// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/RestartableAndQuitable.h"
#include "EndGame.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAMETUTORIAL_API UEndGame : public URestartableAndQuitable
{
	GENERATED_BODY()
public:
	void SetEndGameMessage(bool bIsplayerWinner);

private:
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* EndGameMessage;

	UPROPERTY(EditAnywhere)
	FString WinMessage = "You Win!";
	UPROPERTY(EditAnywhere)
	FString LoseMessage = "You Lose!";
};
