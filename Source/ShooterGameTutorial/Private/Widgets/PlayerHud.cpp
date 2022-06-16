// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PlayerHud.h"

#include "Kismet/GameplayStatics.h"
#include "Characters/Sajjadcomando.h"
#include "Actors/Gun.h"

ASajjadComando* UPlayerHud::GetCharacter() {
	//Get Player Pawn
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	//Cast To SajjadComando
	if (PlayerPawn == nullptr) return nullptr;
	return Cast<ASajjadComando>(PlayerPawn);
}


float UPlayerHud::GetPlayerHealth() {
	return GetCharacter()->GetHealth();
}

int UPlayerHud::GetCurrentAmmo() {
	return GetCharacter()->GetActiveGun()->GetCurrentAmmo();
}

int UPlayerHud::GetAllAmmo() {
	return GetCharacter()->GetActiveGun()->GetAllAmmo();
}