// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "GenericTeamAgentInterface.h"
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

	bool IsEnemyDead();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UFUNCTION()
	void OnPlayerSeen(AActor* Actor, FAIStimulus Stimulus);
	
	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere)
	class UAIPerceptionComponent* AIPerceptionComponent;
	
	class UAISenseConfig_Sight* SightConfig;
};
