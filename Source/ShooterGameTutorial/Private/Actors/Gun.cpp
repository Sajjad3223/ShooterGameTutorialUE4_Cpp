// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Gun.h"

#include "DrawDebugHelpers.h"

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

}

void AGun::Shoot()
{
	//TODO play a Particle System
	//TODO play a Sound

	//Declare Variables
	FVector CameraLocation;
	FRotator CameraRotation;
	
	// Get Camera Location and Rotation
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	OwnerPawn->GetController()->GetPlayerViewPoint(OUT CameraLocation,OUT CameraRotation);

	//Calculate Trace End
	FVector TraceEnd = CameraLocation + CameraRotation.Vector() * TraceRange;
	
	//LineTrace
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(OUT HitResult,CameraLocation,TraceEnd,ECollisionChannel::ECC_GameTraceChannel1);

	//Test Linetrace
	DrawDebugLine(GetWorld(),CameraLocation,TraceEnd,FColor::Red,true,-1,0,5);

	//Check if Hit Something and do the function
}

