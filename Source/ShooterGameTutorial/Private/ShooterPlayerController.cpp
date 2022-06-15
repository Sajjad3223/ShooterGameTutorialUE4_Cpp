// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"

#include "Widgets/PlayerHud.h"
#include "Widgets/PauseMenu.h"
#include "Widgets/EndGame.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "../Public/Widgets/RestartableAndQuitable.h"

AShooterPlayerController::AShooterPlayerController() {
	ConstructorHelpers::FClassFinder<UPlayerHud> PlayerWidget(TEXT("/Game/Widgets/WBP_PlayerHud"));
	ConstructorHelpers::FClassFinder<UPauseMenu> PauseWidget(TEXT("/Game/Widgets/WBP_PauseMenu"));
	ConstructorHelpers::FClassFinder<UEndGame> EndGameWidget(TEXT("/Game/Widgets/WBP_EndGame"));

	if (PlayerWidget.Class != nullptr)
		PlayerHudClass = PlayerWidget.Class;

	if (PauseWidget.Class != nullptr)
		PauseMenuClass = PauseWidget.Class;

	if (EndGameWidget.Class != nullptr)
		EndGameClass = EndGameWidget.Class;
}

void AShooterPlayerController::BeginPlay()
{
	if (PlayerHudClass != nullptr)
	{
		UPlayerHud* PlayerHud = CreateWidget<UPlayerHud>(this,PlayerHudClass);
		PlayerHud->AddToViewport();
	}
}

void AShooterPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	InputComponent->BindAction("Pause", IE_Pressed, this, &AShooterPlayerController::PauseGame);
}

void AShooterPlayerController::PauseGame() {
	if (PauseMenuClass != nullptr)
	{
		UPauseMenu* PauseMenu = CreateWidget<UPauseMenu>(this, PauseMenuClass);

		PauseAndSetupWidget(PauseMenu);

		PauseMenu->AddToViewport();
	}
}

void AShooterPlayerController::ResumeGame() {
	EnableInput(this);
	UGameplayStatics::SetGlobalTimeDilation(this, 1);
	SetShowMouseCursor(false);

	FInputModeGameOnly GameOnly;
	SetInputMode(GameOnly);
}

void AShooterPlayerController::RestartGame() {
	ResumeGame();
	UGameplayStatics::OpenLevel(this, FName("targetsMap"));
}

void AShooterPlayerController::QuitGame() {
	ConsoleCommand("Quit");
}

void AShooterPlayerController::PauseAndSetupWidget(URestartableAndQuitable* Widget) {
	DisableInput(this);
	UGameplayStatics::SetGlobalTimeDilation(this, 0);
	SetShowMouseCursor(true);

	FInputModeUIOnly UiMode;
	SetInputMode(UiMode);

	Widget->SetupController(this);
}

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner) {
	if (EndGameClass != nullptr) {
		UEndGame* EndGame = CreateWidget<UEndGame>(this, EndGameClass);

		PauseAndSetupWidget(EndGame);

		EndGame->SetEndGameMessage(bIsWinner);

		EndGame->AddToViewport();
	}
}