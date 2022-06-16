// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterHack.h"

#include "Kismet/GameplayStatics.h"
#include "./Characters/SajjadComando.h"
#include "./Actors/Gun.h"

void UShooterHack::HackGun(int Ammo) {
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	Cast<ASajjadComando>(Pawn)->GetActiveGun()->SetAmmo(Ammo);
}

void UShooterHack::HackHealth(int Health) {
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	Cast<ASajjadComando>(Pawn)->SetHealth(Health);
}