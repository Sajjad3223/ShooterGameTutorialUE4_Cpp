// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/EndGame.h"

#include "Components/TextBlock.h"

void UEndGame::SetEndGameMessage(bool bIsplayerWinner) {
	FString Message = bIsplayerWinner ? WinMessage : LoseMessage;
		
	EndGameMessage->SetText(FText::FromString(Message));
}