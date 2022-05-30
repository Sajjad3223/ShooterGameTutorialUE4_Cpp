// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SajjadComando.h"

#include "Actors/Gun.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
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

	Health = MaxHealth;
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
	PlayerInputComponent->BindAction("Fire",IE_Pressed,this,&ASajjadComando::StartFire);
	PlayerInputComponent->BindAction("Fire",IE_Released,this,&ASajjadComando::StopFire);
}

float ASajjadComando::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	Health -= FMath::Min(Health,Damage);; // Health = Health - FMath::Min(Health,Damage)

	UE_LOG(LogTemp,Warning,TEXT("Health is: %f"),Health);
	if(IsDead())
	{
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		FTimerHandle DestroyTimer;
		GetWorldTimerManager().SetTimer(DestroyTimer,this,&ASajjadComando::DestroyCharacter,DestroyDelay,false);
	}
	
	return Damage;
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

void ASajjadComando::StartFire()
{
	Gun->StartShoot();
}

void ASajjadComando::StopFire()
{
	Gun->EndShoot();
}

bool ASajjadComando::IsDead()
{
	return Health <= 0;
}

void ASajjadComando::DestroyCharacter()
{
	Gun->Destroy();
	Destroy();
}
