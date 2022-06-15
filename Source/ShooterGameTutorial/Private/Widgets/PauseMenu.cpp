// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PauseMenu.h"

#include "Components/Button.h"
#include "../../Public/ShooterPlayerController.h"

bool UPauseMenu::Initialize() {
	bool bSuccess = Super::Initialize();
	if (!bSuccess) return false;

	Resume->OnClicked.AddDynamic(this, &UPauseMenu::ResumeGame);

	return true;
}

void UPauseMenu::ResumeGame() {
	if (PlayerController == nullptr) return;
	PlayerController->ResumeGame();
	RemoveFromParent();
}