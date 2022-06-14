// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"

#include "Widgets/PlayerHud.h"
#include "UObject/ConstructorHelpers.h"

AShooterPlayerController::AShooterPlayerController() {
	ConstructorHelpers::FClassFinder<UPlayerHud> PlayerWidget(TEXT("/Game/Widgets/WBP_PlayerHud"));
	if (PlayerWidget.Class != nullptr)
		PlayerHudClass = PlayerWidget.Class;
}

void AShooterPlayerController::BeginPlay()
{
	if (PlayerHudClass != nullptr)
	{
		UPlayerHud* PlayerHud = CreateWidget<UPlayerHud>(this,PlayerHudClass);
		PlayerHud->AddToViewport();
	}
}
