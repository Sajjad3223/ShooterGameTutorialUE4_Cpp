// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"

#include "Widgets/PlayerHud.h"
#include "Widgets/PauseMenu.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AShooterPlayerController::AShooterPlayerController() {
	ConstructorHelpers::FClassFinder<UPlayerHud> PlayerWidget(TEXT("/Game/Widgets/WBP_PlayerHud"));
	ConstructorHelpers::FClassFinder<UPauseMenu> PauseWidget(TEXT("/Game/Widgets/WBP_PauseMenu"));

	if (PlayerWidget.Class != nullptr)
		PlayerHudClass = PlayerWidget.Class;

	if (PauseWidget.Class != nullptr)
		PauseMenuClass = PauseWidget.Class;
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

		DisableInput(this);
		UGameplayStatics::SetGlobalTimeDilation(this, 0);
		SetShowMouseCursor(true);

		FInputModeUIOnly UiMode;
		SetInputMode(UiMode);

		PauseMenu->SetupController(this);

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