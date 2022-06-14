// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAMETUTORIAL_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AShooterPlayerController();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	TSubclassOf<class UPlayerHud> PlayerHudClass;
};
