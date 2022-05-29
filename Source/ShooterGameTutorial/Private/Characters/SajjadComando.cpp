// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SajjadComando.h"

#include "Actors/Gun.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASajjadComando::ASajjadComando()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("CameraBoom"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ASajjadComando::BeginPlay()
{
	Super::BeginPlay();

	// Hide the bone which has a gun
	GetMesh()->HideBoneByName(FName("gun"),EPhysBodyOp::PBO_None);

	//  spawn a gun and attach it to character
	if(GunClass)
	{
		Gun = GetWorld()->SpawnActor<AGun>(GunClass);
		Gun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,FName("WeaponSocket"));
		Gun->SetOwner(this);
	}
	
}

// Called every frame
void ASajjadComando::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASajjadComando::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward",this,&ASajjadComando::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ASajjadComando::MoveRight);
	PlayerInputComponent->BindAxis("Turn",this,&ASajjadComando::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnUp",this,&ASajjadComando::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRate",this,&ASajjadComando::Turn);
	PlayerInputComponent->BindAxis("TurnUpRate",this,&ASajjadComando::TurnUp);
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ASajjadComando::Jump);
	PlayerInputComponent->BindAction("Fire",IE_Pressed,this,&ASajjadComando::Fire);
}

void ASajjadComando::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void ASajjadComando::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void ASajjadComando::Turn(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotateSensitivity * GetWorld()->GetDeltaSeconds());
}

void ASajjadComando::TurnUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotateSensitivity * GetWorld()->GetDeltaSeconds());
}

void ASajjadComando::Fire()
{
	Gun->Shoot();
}
