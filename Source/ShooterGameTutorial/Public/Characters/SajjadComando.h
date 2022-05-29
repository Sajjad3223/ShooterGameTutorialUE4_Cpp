// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SajjadComando.generated.h"

class AGun;

UCLASS()
class SHOOTERGAMETUTORIAL_API ASajjadComando : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASajjadComando();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Turn(float AxisValue);
	void TurnUp(float AxisValue);

	void Fire();

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere)
	float RotateSensitivity = 60;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AGun> GunClass;

	AGun* Gun;
};
