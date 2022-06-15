// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/RestartableAndQuitable.h"

#include "Components/Button.h"
#include "../../Public/ShooterPlayerController.h"

bool URestartableAndQuitable::Initialize() {
	bool bSuccess = Super::Initialize();
	if (!bSuccess) return false;

	Restart->OnClicked.AddDynamic(this, &URestartableAndQuitable::RestartGame);
	Quit->OnClicked.AddDynamic(this, &URestartableAndQuitable::QuitGame);

	return true;
}
void URestartableAndQuitable::SetupController(AShooterPlayerController* playerController) {
	PlayerController = playerController;
}
void URestartableAndQuitable::RestartGame() {
	if (PlayerController == nullptr) return;
	PlayerController->RestartGame();
}

void URestartableAndQuitable::QuitGame() {
	if (PlayerController == nullptr) return;
	PlayerController->QuitGame();
}