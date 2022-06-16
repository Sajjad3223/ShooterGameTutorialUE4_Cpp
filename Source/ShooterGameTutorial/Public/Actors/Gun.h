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

	//Shoot Functions
	void StartShoot();
	void EndShoot();
	void Reload();
	void Fire();

	int GetCurrentAmmo();
	int GetAllAmmo();

	void SetAmmo(int Ammo);

protected:
	virtual void BeginPlay() override;
private:
	AController* GetPlayerController();
	void PlayEffects();
	bool RayCast(FHitResult& HitResult, FVector& CameraLocation);
	void PlayEffectsOnHit(FHitResult HitResult);

	void Shoot();

	UPROPERTY(EditAnywhere)
	int MaxAmmo = 100;
	UPROPERTY(EditAnywhere)
	int MaxMagAmmo = 30;

	int MaxHoldingAmmo;
	int CurrentAmmo;

	bool bIsShooting = false;
	float FireTimer = 0;
	
	UPROPERTY(EditAnywhere)
	float FireRate = 0.2f;
	
	// Scene Component
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	//Skeletal Mesh Component
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* GunMesh;

	//Range for Line trace
	UPROPERTY(EditAnywhere)
	float TraceRange = 10000;

	//Gun Damage
	UPROPERTY(EditAnywhere)
	float Damage = 20;

	//Particle System for fire
	UPROPERTY(EditAnywhere)
	UParticleSystem* FireParticleSystem = nullptr;
	
	//Particle System for Impact
	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactParticleSystem = nullptr;

	UPROPERTY(EditAnywhere)
	USoundBase* ShootSound = nullptr;
	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound = nullptr;
};
