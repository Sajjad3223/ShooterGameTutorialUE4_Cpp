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

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bIsShooting)
	{
		if(FireTimer >= FireRate)
		{
			Shoot();
			FireTimer = 0;
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

void AGun::Fire() {
	Shoot();
}

void AGun::Shoot()
{
	if(FireParticleSystem != nullptr)
	{
		UGameplayStatics::SpawnEmitterAttached(FireParticleSystem,GunMesh,FName("MuzzleFlashSocket"));
	}
	//TODO play a Sound

	//Declare Variables
	FVector CameraLocation;
	FRotator CameraRotation;
	
	// Get Camera Location and Rotation
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	AController* OwnerController = OwnerPawn->GetController();
	OwnerController->GetPlayerViewPoint(OUT CameraLocation,OUT CameraRotation);

	//Calculate Trace End
	FVector TraceEnd = CameraLocation + CameraRotation.Vector() * TraceRange;
	
	//LineTrace
	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	if(GetWorld()->LineTraceSingleByChannel(OUT HitResult,CameraLocation,TraceEnd,ECollisionChannel::ECC_GameTraceChannel1,Params))
	{
		//Check if Hit Something and do the function
		
		//Spawn Emitter
		if(ImpactParticleSystem != nullptr)
			UGameplayStatics::SpawnEmitterAtLocation(this,ImpactParticleSystem,HitResult.Location,HitResult.ImpactNormal.Rotation());

		//Play Sound


		FVector ShotDirection = HitResult.Location - CameraLocation;
		
		//Apply Damage
		if(HitResult.Actor != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage,HitResult,ShotDirection,nullptr);
			HitResult.Actor->TakeDamage(Damage,DamageEvent,OwnerController,this);
		}
	}

	
}

