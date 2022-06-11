// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAMETUTORIAL_API AEnemyController : public AAIController
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AEnemyController();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviorTree;

	APawn* PlayerPawn;
};
