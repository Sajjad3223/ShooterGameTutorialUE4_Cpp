// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SHOOTERGAMETUTORIAL_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Shoot Function
	void Shoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	// Scene Component
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	//Skeletal Mesh Component
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* GunMesh;

	//Range for Line trace
	UPROPERTY(EditAnywhere)
	float TraceRange = 10000;
};
