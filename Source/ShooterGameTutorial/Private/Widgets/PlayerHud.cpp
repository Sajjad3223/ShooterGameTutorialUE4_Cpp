// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PlayerHud.h"

#include "Kismet/GameplayStatics.h"
#include "Characters/Sajjadcomando.h"

float UPlayerHud::GetPlayerHealth() {
	//Get Player Pawn
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	//Cast To SajjadComando
	if (PlayerPawn == nullptr) return 0;
	ASajjadComando* Character = Cast<ASajjadComando>(PlayerPawn);

	//Return health
	if (Character == nullptr)return 0;
	
	return Character->GetHealth();
	
}