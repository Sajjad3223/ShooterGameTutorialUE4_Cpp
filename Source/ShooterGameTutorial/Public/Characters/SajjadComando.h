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
	
	//Override Receive any damage
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
private:
	//Axis Functions
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Turn(float AxisValue);
	void TurnUp(float AxisValue);

	//Action Functions
	void StartFire();
	void StopFire();

	//Components
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere)
	float RotateSensitivity = 60;

	//Gun Properties
	UPROPERTY(EditAnywhere)
	TSubclassOf<AGun> GunClass;
	AGun* Gun;

	//Health Properties
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100;
	float Health;
};
