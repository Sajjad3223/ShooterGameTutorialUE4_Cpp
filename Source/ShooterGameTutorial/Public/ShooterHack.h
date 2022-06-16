// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "ShooterHack.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAMETUTORIAL_API UShooterHack : public UCheatManager
{
	GENERATED_BODY()
private:
	UFUNCTION(Exec)
	void HackGun(int Ammo = 999);

	UFUNCTION(Exec)
	void HackHealth(int Health = 999);
};
