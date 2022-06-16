// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Gun.h"

#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

#define OUT

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	RootComponent = Root;
	
	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Gun"));
	GunMesh->SetupAttachment(Root);
}

void AGun::BeginPlay() {
	Super::BeginPlay();
	CurrentAmmo = MaxMagAmmo;
	MaxHoldingAmmo = MaxAmmo;
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bIsShooting)
	{
		if(FireTimer >= FireRate)
		{
			if (CurrentAmmo > 0)
			{
				Shoot();
				FireTimer = 0;
			}
		}
	}
	
	FireTimer += DeltaTime;
}

void AGun::StartShoot()
{
	bIsShooting = true;
}

void AGun::EndShoot()
{
	bIsShooting = false;
}

void AGun::Reload()
{
	if (CurrentAmmo >= MaxMagAmmo) return;

	int AvailableAmmo = FMath::Min<int>(MaxMagAmmo, MaxHoldingAmmo);

	MaxHoldingAmmo -= AvailableAmmo - CurrentAmmo;

	CurrentAmmo = AvailableAmmo;
}

void AGun::Fire() {
	if (CurrentAmmo > 0)
	{
		Shoot();
	}
	else {
		Reload();
	}
}

int AGun::GetCurrentAmmo()
{
	return CurrentAmmo;
}
int AGun::GetAllAmmo()
{
	return MaxHoldingAmmo;
}

void AGun::PlayEffects() {
	if (FireParticleSystem != nullptr)
		UGameplayStatics::SpawnEmitterAttached(FireParticleSystem, GunMesh, FName("MuzzleFlashSocket"));
	if (ShootSound != nullptr)
		UGameplayStatics::SpawnSoundAttached(ShootSound, GunMesh, FName("MuzzleFlashSocket"));
}

AController* AGun::GetPlayerController() {
	// Get Camera Location and Rotation
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	return OwnerPawn->GetController();
}

bool AGun::RayCast(FHitResult& HitResult, FVector& CameraLocation) {
	//Declare Variables
	FRotator CameraRotation;
	GetPlayerController()->GetPlayerViewPoint(OUT CameraLocation, OUT CameraRotation);

	//Calculate Trace End
	FVector TraceEnd = CameraLocation + CameraRotation.Vector() * TraceRange;

	//LineTrace
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(OUT HitResult, CameraLocation, TraceEnd, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

void AGun::PlayEffectsOnHit(FHitResult HitResult) {
	//Spawn Emitter
	if (ImpactParticleSystem != nullptr)
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactParticleSystem, HitResult.Location, HitResult.ImpactNormal.Rotation());

	//Play Sound
	if (ImpactSound != nullptr)
		UGameplayStatics::SpawnSoundAtLocation(this, ImpactSound, HitResult.Location, HitResult.ImpactNormal.Rotation());
}

void AGun::Shoot()
{
	CurrentAmmo--;
	PlayEffects();

	FVector CameraLocation;
	FHitResult HitResult;

	if(RayCast(HitResult,CameraLocation))
	{
		PlayEffectsOnHit(HitResult);

		FVector ShotDirection = HitResult.Location - CameraLocation;
		//Apply Damage
		if(HitResult.Actor != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage,HitResult,ShotDirection,nullptr);
			HitResult.Actor->TakeDamage(Damage,DamageEvent, GetPlayerController(),this);
		}
	}

	
}

