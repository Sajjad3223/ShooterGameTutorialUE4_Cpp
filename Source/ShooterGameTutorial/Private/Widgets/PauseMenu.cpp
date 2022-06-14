// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PauseMenu.h"

#include "Components/Button.h"
#include "../../Public/ShooterPlayerController.h"

bool UPauseMenu::Initialize() {
	bool bSuccess = Super::Initialize();
	if (!bSuccess) return false;

	Resume->OnClicked.AddDynamic(this, &UPauseMenu::ResumeGame);
	Restart->OnClicked.AddDynamic(this, &UPauseMenu::RestartGame);
	Quit->OnClicked.AddDynamic(this, &UPauseMenu::QuitGame);

	return true;
}

void UPauseMenu::SetupController(AShooterPlayerController* playerController){
	PlayerController = playerController;
}

void UPauseMenu::ResumeGame() {
	if (PlayerController == nullptr) return;
	PlayerController->ResumeGame();
	RemoveFromParent();
}

void UPauseMenu::RestartGame() {
	if (PlayerController == nullptr) return;
	PlayerController->RestartGame();
}

void UPauseMenu::QuitGame() {
	if (PlayerController == nullptr) return;
	PlayerController->QuitGame();
}